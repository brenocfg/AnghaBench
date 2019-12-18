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
struct command {int t_dcom; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_EMPTYIF ; 
 int ERR_IMPRTHEN ; 
 int ERR_NAME ; 
 int /*<<< orphan*/  STRthen ; 
 int /*<<< orphan*/  TC_IF ; 
 int /*<<< orphan*/  donefds () ; 
 scalar_t__ eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int expr (int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/  lshift (int,int /*<<< orphan*/ **) ; 
 scalar_t__ noexec ; 
 int /*<<< orphan*/  reexecute (struct command*) ; 
 int /*<<< orphan*/  search (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int) ; 

void
doif(Char **v, struct command *kp)
{
    int i;
    Char **vv;

    v++;
    i = noexec ? 1 : expr(&v);
    vv = v;
    if (*vv == NULL)
	stderror(ERR_NAME | ERR_EMPTYIF);
    if (eq(*vv, STRthen)) {
	if (*++vv)
	    stderror(ERR_NAME | ERR_IMPRTHEN);
	setname(short2str(STRthen));
	/*
	 * If expression was zero, then scan to else , otherwise just fall into
	 * following code.
	 */
	if (!i)
	    search(TC_IF, 0, NULL);
	return;
    }
    /*
     * Simple command attached to this if. Left shift the node in this tree,
     * munging it so we can reexecute it.
     */
    if (i) {
	lshift(kp->t_dcom, vv - kp->t_dcom);
	reexecute(kp);
	donefds();
    }
}