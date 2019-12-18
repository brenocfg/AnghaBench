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
typedef  char Char ;

/* Variables and functions */
 char* Cursor ; 
 char HIST ; 
 char* InputBuf ; 
 char* c_expand (char*) ; 

__attribute__((used)) static int
c_excl(Char *p)
{
    int i;
    Char *q;
    int nr_exp;

    /*
     * if />[SPC TAB]*![SPC TAB]/, back up p to just after the >. otherwise,
     * back p up to just before the current word.
     */
    if ((p[1] == ' ' || p[1] == '\t') &&
	(p[-1] == ' ' || p[-1] == '\t' || p[-1] == '>')) {
	for (q = p - 1; q > InputBuf && (*q == ' ' || *q == '\t'); --q)
	    continue;
	if (*q == '>')
	    ++p;
    }
    else {
	while (*p != ' ' && *p != '\t' && p > InputBuf)
	    --p;
    }

    /*
     * Forever: Look for history char.  (Stop looking when we find the cursor.)
     * Count backslashes.  If odd, skip history char.  Expand if even number of
     * backslashes.
     */
    nr_exp = 0;
    for (;;) {
	if (HIST != '\0')
	    while (*p != HIST && p < Cursor)
		++p;
	for (i = 1; (p - i) >= InputBuf && p[-i] == '\\'; i++)
	    continue;
	if (i % 2 == 0)
	    ++p;
	if (p >= Cursor)   /* all done */
	    return nr_exp;
	if (i % 2 == 1) {
	    p = c_expand(p);
	    ++nr_exp;
	}
    }
}