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
struct command {int /*<<< orphan*/  t_dflg; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_REPEAT ; 
 int /*<<< orphan*/  F_SAVE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  execute (struct command*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tpgrp ; 

void
reexecute(struct command *kp)
{
    kp->t_dflg &= F_SAVE;
    kp->t_dflg |= F_REPEAT;
    /*
     * If tty is still ours to arbitrate, arbitrate it; otherwise dont even set
     * pgrp's as the jobs would then have no way to get the tty (we can't give
     * it to them, and our parent wouldn't know their pgrp, etc.
     */
    execute(kp, (tpgrp > 0 ? tpgrp : -1), NULL, NULL, TRUE);
}