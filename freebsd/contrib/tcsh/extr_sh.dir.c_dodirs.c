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
struct directory {struct directory* di_prev; struct directory* di_next; } ;
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int DIR_CLEAR ; 
 int DIR_LOAD ; 
 int DIR_OLD ; 
 int DIR_PRINT ; 
 int DIR_SAVE ; 
 int /*<<< orphan*/  ERR_DIRUS ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 struct directory* dcwd ; 
 int /*<<< orphan*/  dfree (struct directory*) ; 
 struct directory dhead ; 
 int /*<<< orphan*/  loaddirs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printdirs (int) ; 
 int /*<<< orphan*/  recdirs (int /*<<< orphan*/ *,int) ; 
 int skipargs (int /*<<< orphan*/ ***,char const*,char*) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,char*,char const*,char*) ; 

void
dodirs(Char **v, struct command *c)
{
    static const char flags[] = "plvnSLc";
    int dflag = skipargs(&v, flags, "");

    USE(c);
    if ((dflag & DIR_CLEAR) != 0) {
	struct directory *dp, *fdp;
	for (dp = dcwd->di_next; dp != dcwd; ) {
	    fdp = dp;
	    dp = dp->di_next;
	    if (fdp != &dhead)
		dfree(fdp);
	}
	dhead.di_next = dhead.di_prev = dp;
	dp->di_next = dp->di_prev = &dhead;
    }
    if ((dflag & DIR_LOAD) != 0) 
	loaddirs(*v);
    else if ((dflag & DIR_SAVE) != 0)
	recdirs(*v, 1);

    if (*v && (dflag & (DIR_SAVE|DIR_LOAD)))
	v++;

    if (*v != NULL || (dflag & DIR_OLD))
	stderror(ERR_DIRUS, "dirs", flags, "");
    if ((dflag & (DIR_CLEAR|DIR_LOAD|DIR_SAVE)) == 0 || (dflag & DIR_PRINT))
	printdirs(dflag);
}