#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ verbose; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int EOF ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (unsigned char) ; 
 TYPE_1__ opt ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  set_option (char*) ; 

__attribute__((used)) static void
scan_profile(FILE *f)
{
    int		comment, i;
    char	*p;
    char        buf[BUFSIZ];

    while (1) {
	p = buf;
	comment = 0;
	while ((i = getc(f)) != EOF) {
	    if (i == '*' && !comment && p > buf && p[-1] == '/') {
		comment = p - buf;
		*p++ = i;
	    } else if (i == '/' && comment && p > buf && p[-1] == '*') {
		p = buf + comment - 1;
		comment = 0;
	    } else if (isspace((unsigned char)i)) {
		if (p > buf && !comment)
		    break;
	    } else {
		*p++ = i;
	    }
	}
	if (p != buf) {
	    *p++ = 0;
	    if (opt.verbose)
		printf("profile: %s\n", buf);
	    set_option(buf);
	}
	else if (i == EOF)
	    return;
    }
}