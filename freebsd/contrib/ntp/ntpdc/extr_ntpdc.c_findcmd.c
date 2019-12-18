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
struct xcmd {char* keyword; } ;

/* Variables and functions */
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,unsigned int) ; 

__attribute__((used)) static int
findcmd(
	register char *str,
	struct xcmd *clist1,
	struct xcmd *clist2,
	struct xcmd **cmd
	)
{
	register struct xcmd *cl;
	size_t clen;
	int nmatch;
	struct xcmd *nearmatch = NULL;
	struct xcmd *clist;

	clen = strlen(str);
	nmatch = 0;
	if (clist1 != 0)
	    clist = clist1;
	else if (clist2 != 0)
	    clist = clist2;
	else
	    return 0;

    again:
	for (cl = clist; cl->keyword != 0; cl++) {
		/* do a first character check, for efficiency */
		if (*str != *(cl->keyword))
		    continue;
		if (strncmp(str, cl->keyword, (unsigned)clen) == 0) {
			/*
			 * Could be extact match, could be approximate.
			 * Is exact if the length of the keyword is the
			 * same as the str.
			 */
			if (*((cl->keyword) + clen) == '\0') {
				*cmd = cl;
				return 1;
			}
			nmatch++;
			nearmatch = cl;
		}
	}

				/*
				 * See if there is more to do.  If so, go again.  Sorry about the
				 * goto, too much looking at BSD sources...
				 */
	if (clist == clist1 && clist2 != 0) {
		clist = clist2;
		goto again;
	}

				/*
				 * If we got extactly 1 near match, use it, else return number
				 * of matches.
				 */
	if (nmatch == 1) {
		*cmd = nearmatch;
		return 1;
	}
	return nmatch;
}