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
 int /*<<< orphan*/  STRstatus ; 
 int /*<<< orphan*/  _mcleanup () ; 
 int child ; 
 int /*<<< orphan*/  getn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xexit (int /*<<< orphan*/ ) ; 

void
exitstat(void)
{
#ifdef PROF
    _mcleanup();
#endif
    /*
     * Note that if STATUS is corrupted (i.e. getn bombs) then error will exit
     * directly because we poke child here. Otherwise we might continue
     * unwarrantedly (sic).
     */
    child = 1;

    xexit(getn(varval(STRstatus)));
}