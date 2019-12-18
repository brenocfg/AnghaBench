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

/* Variables and functions */
 int /*<<< orphan*/  FSHTTY ; 
 int /*<<< orphan*/  STR1 ; 
 int /*<<< orphan*/  STRstatus ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/  btoeof () ; 
 scalar_t__ child ; 
 scalar_t__ didfds ; 
 scalar_t__ exiterr ; 
 int /*<<< orphan*/  exitset ; 
 int /*<<< orphan*/  setcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcsetpgrp (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tpgrp ; 
 int /*<<< orphan*/  xexit (int) ; 

void
fixerror(void)
{
    didfds = 0;			/* Forget about 0,1,2 */
    /*
     * Go away if -e or we are a child shell
     */
    if (!exitset || exiterr || child)
	xexit(1);

    /*
     * Reset the state of the input. This buffered seek to end of file will
     * also clear the while/foreach stack.
     */
    btoeof();

    setcopy(STRstatus, STR1, VAR_READWRITE);/*FIXRESET*/
#ifdef BSDJOBS
    if (tpgrp > 0)
	(void) tcsetpgrp(FSHTTY, tpgrp);
#endif
}