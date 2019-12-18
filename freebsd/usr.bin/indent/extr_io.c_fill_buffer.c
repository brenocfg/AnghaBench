#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 char* be_save ; 
 char* bp_save ; 
 char* buf_end ; 
 char* buf_ptr ; 
 int /*<<< orphan*/  dump_line () ; 
 scalar_t__ e_code ; 
 scalar_t__ e_com ; 
 scalar_t__ e_lab ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int had_eof ; 
 char* in_buffer ; 
 char* in_buffer_limit ; 
 int inhibit_formatting ; 
 int /*<<< orphan*/ * input ; 
 scalar_t__ n_real_blanklines ; 
 int /*<<< orphan*/  output ; 
 scalar_t__ postfix_blankline_requested ; 
 scalar_t__ prefix_blankline_requested ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 char* realloc (char*,int) ; 
 scalar_t__ s_code ; 
 scalar_t__ s_com ; 
 scalar_t__ s_lab ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int suppress_blanklines ; 

void
fill_buffer(void)
{				/* this routine reads stuff from the input */
    char *p;
    int i;
    FILE *f = input;

    if (bp_save != NULL) {	/* there is a partly filled input buffer left */
	buf_ptr = bp_save;	/* do not read anything, just switch buffers */
	buf_end = be_save;
	bp_save = be_save = NULL;
	if (buf_ptr < buf_end)
	    return;		/* only return if there is really something in
				 * this buffer */
    }
    for (p = in_buffer;;) {
	if (p >= in_buffer_limit) {
	    int size = (in_buffer_limit - in_buffer) * 2 + 10;
	    int offset = p - in_buffer;
	    in_buffer = realloc(in_buffer, size);
	    if (in_buffer == NULL)
		errx(1, "input line too long");
	    p = in_buffer + offset;
	    in_buffer_limit = in_buffer + size - 2;
	}
	if ((i = getc(f)) == EOF) {
		*p++ = ' ';
		*p++ = '\n';
		had_eof = true;
		break;
	}
	if (i != '\0')
	    *p++ = i;
	if (i == '\n')
		break;
    }
    buf_ptr = in_buffer;
    buf_end = p;
    if (p - in_buffer > 2 && p[-2] == '/' && p[-3] == '*') {
	if (in_buffer[3] == 'I' && strncmp(in_buffer, "/**INDENT**", 11) == 0)
	    fill_buffer();	/* flush indent error message */
	else {
	    int         com = 0;

	    p = in_buffer;
	    while (*p == ' ' || *p == '\t')
		p++;
	    if (*p == '/' && p[1] == '*') {
		p += 2;
		while (*p == ' ' || *p == '\t')
		    p++;
		if (p[0] == 'I' && p[1] == 'N' && p[2] == 'D' && p[3] == 'E'
			&& p[4] == 'N' && p[5] == 'T') {
		    p += 6;
		    while (*p == ' ' || *p == '\t')
			p++;
		    if (*p == '*')
			com = 1;
		    else if (*p == 'O') {
			if (*++p == 'N')
			    p++, com = 1;
			else if (*p == 'F' && *++p == 'F')
			    p++, com = 2;
		    }
		    while (*p == ' ' || *p == '\t')
			p++;
		    if (p[0] == '*' && p[1] == '/' && p[2] == '\n' && com) {
			if (s_com != e_com || s_lab != e_lab || s_code != e_code)
			    dump_line();
			if (!(inhibit_formatting = com - 1)) {
			    n_real_blanklines = 0;
			    postfix_blankline_requested = 0;
			    prefix_blankline_requested = 0;
			    suppress_blanklines = 1;
			}
		    }
		}
	    }
	}
    }
    if (inhibit_formatting) {
	p = in_buffer;
	do
	    putc(*p, output);
	while (*p++ != '\n');
    }
}