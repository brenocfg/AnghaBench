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
struct Hist {int /*<<< orphan*/  Href; int /*<<< orphan*/  Hnum; struct Hist* Hnext; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 struct Hist Histlist ; 
 int /*<<< orphan*/ * STRNULL ; 
 int /*<<< orphan*/  STRhistfile ; 
 int /*<<< orphan*/ * STRmh ; 
 int /*<<< orphan*/ * STRmm ; 
#define  STRsource 128 
 int /*<<< orphan*/ * STRtildothist ; 
 int /*<<< orphan*/  dosource (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int eventno ; 
 int /*<<< orphan*/ * varval (int /*<<< orphan*/ ) ; 

void
loadhist(Char *fname, int mflg)
{
    static Char   *loadhist_cmd[] = {STRsource, NULL, NULL, NULL};
    loadhist_cmd[1] = mflg ? STRmm : STRmh;

    if (fname != NULL)
	loadhist_cmd[2] = fname;
    else if ((fname = varval(STRhistfile)) != STRNULL)
	loadhist_cmd[2] = fname;
    else
	loadhist_cmd[2] = STRtildothist;

    dosource(loadhist_cmd, NULL);

    /* During history merging (enthist sees mflg set), we disable management of
     * Hnum and Href (because fastMergeErase is true).  So now reset all the
     * values based on the final ordering of the history list. */
    if (mflg) {
	int n = eventno;
        struct Hist *hp = &Histlist;
        while ((hp = hp->Hnext))
	    hp->Hnum = hp->Href = n--;
    }
}