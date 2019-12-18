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
struct directory {struct directory* di_prev; struct directory* di_next; int /*<<< orphan*/  di_name; } ;
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int DIR_OLD ; 
 int ERR_BADDIR ; 
 int ERR_EMPTY ; 
 int ERR_NAME ; 
 int /*<<< orphan*/  ERR_SYSTEM ; 
 int ERR_TOOMANY ; 
 int /*<<< orphan*/  STRowd ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 scalar_t__ chdir (char*) ; 
 struct directory* dcwd ; 
 struct directory* dfind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfree (struct directory*) ; 
 struct directory dhead ; 
 int /*<<< orphan*/  dnewcwd (struct directory*,int) ; 
 int /*<<< orphan*/  errno ; 
 int printd ; 
 int /*<<< orphan*/  printdirs (int) ; 
 char* short2str (int /*<<< orphan*/ ) ; 
 int skipargs (int /*<<< orphan*/ ***,char*,char*) ; 
 int /*<<< orphan*/  stderror (int,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * varval (int /*<<< orphan*/ ) ; 

void
dopopd(Char **v, struct command *c)
{
    Char *cp;
    struct directory *dp, *p = NULL;
    int dflag = skipargs(&v, "plvn", " [-|+<n>]");

    USE(c);
    printd = 1;
    cp = (dflag & DIR_OLD) ? varval(STRowd) : *v;

    if (cp == NULL)
	dp = dcwd;
    else if ((dflag & DIR_OLD) == 0 && v[1] != NULL) {
	stderror(ERR_NAME | ERR_TOOMANY);
	/* NOTREACHED */
	return;
    }
    else if ((dp = dfind(cp)) == 0)
	stderror(ERR_NAME | ERR_BADDIR);
    if (dp->di_prev == &dhead && dp->di_next == &dhead)
	stderror(ERR_NAME | ERR_EMPTY);
    if (dp == dcwd) {
	char   *tmp;

	if ((p = dp->di_prev) == &dhead)
	    p = dhead.di_prev;
	if (chdir(tmp = short2str(p->di_name)) < 0)
	    stderror(ERR_SYSTEM, tmp, strerror(errno));
    }
    dp->di_prev->di_next = dp->di_next;
    dp->di_next->di_prev = dp->di_prev;
    dfree(dp);
    if (dp == dcwd) {
        dnewcwd(p, dflag);
    }
    else {
	printdirs(dflag);
    }
}