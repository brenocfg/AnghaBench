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
typedef  int Char ;

/* Variables and functions */
 int PATHSEP ; 
 int* STRdot ; 
 int /*<<< orphan*/  STRpath ; 
 int* Strsave (int*) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/  blk_cleanup ; 
 int /*<<< orphan*/  cleanup_ignore (int**) ; 
 int /*<<< orphan*/  cleanup_push (int**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int**) ; 
 int /*<<< orphan*/  setq (int /*<<< orphan*/ ,int**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shvhed ; 
 int** xcalloc (size_t,int) ; 

void
importpath(Char *cp)
{
    size_t i = 0;
    Char *dp;
    Char **pv;
    int     c;

    for (dp = cp; *dp; dp++)
	if (*dp == PATHSEP)
	    i++;
    /*
     * i+2 where i is the number of colons in the path. There are i+1
     * directories in the path plus we need room for a zero terminator.
     */
    pv = xcalloc(i + 2, sizeof(Char *));
    dp = cp;
    i = 0;
    if (*dp)
	for (;;) {
	    if ((c = *dp) == PATHSEP || c == 0) {
		*dp = 0;
		pv[i++] = Strsave(*cp ? cp : STRdot);
		if (c) {
		    cp = dp + 1;
		    *dp = PATHSEP;
		}
		else
		    break;
	    }
#ifdef WINNT_NATIVE
	    else if (*dp == '\\')
		*dp = '/';
#endif /* WINNT_NATIVE */
	    dp++;
	}
    pv[i] = 0;
    cleanup_push(pv, blk_cleanup);
    setq(STRpath, pv, &shvhed, VAR_READWRITE);
    cleanup_ignore(pv);
    cleanup_until(pv);
}