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
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_HFLAG ; 
 int ERR_MFLAG ; 
 int ERR_NAME ; 
 int /*<<< orphan*/  ERR_SYSTEM ; 
 int /*<<< orphan*/  G_ERROR ; 
 int /*<<< orphan*/  STRmh ; 
 int /*<<< orphan*/  STRmm ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  bequiet ; 
 int /*<<< orphan*/  blk_cleanup ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 scalar_t__ eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ ** glob_all_or_error (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * globone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcfile (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderror (int,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* strsave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
dosource(Char **t, struct command *c)
{
    Char *f;
    int    hflg = 0;
    char *file;

    USE(c);
    t++;
    if (*t && eq(*t, STRmh)) {
	if (*++t == NULL)
	    stderror(ERR_NAME | ERR_HFLAG);
	hflg++;
    }
    else if (*t && eq(*t, STRmm)) {
    	if (*++t == NULL)
	    stderror(ERR_NAME | ERR_MFLAG);
	hflg = 2;
    }

    f = globone(*t++, G_ERROR);
    file = strsave(short2str(f));
    cleanup_push(file, xfree);
    xfree(f);
    t = glob_all_or_error(t);
    cleanup_push(t, blk_cleanup);
    if ((!srcfile(file, 0, hflg, t)) && (!hflg) && (!bequiet))
	stderror(ERR_SYSTEM, file, strerror(errno));
    cleanup_until(file);
}