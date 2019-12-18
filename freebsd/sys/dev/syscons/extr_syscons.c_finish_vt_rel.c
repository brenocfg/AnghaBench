#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int status; TYPE_3__* sc; } ;
typedef  TYPE_1__ scr_stat ;
struct TYPE_5__ {scalar_t__ switch_in_progress; TYPE_1__* old_scp; } ;

/* Variables and functions */
 int EINVAL ; 
 int SWITCH_WAIT_REL ; 
 int do_switch_scr (TYPE_3__*,int) ; 

__attribute__((used)) static int
finish_vt_rel(scr_stat *scp, int release, int *s)
{
    if (scp == scp->sc->old_scp && scp->status & SWITCH_WAIT_REL) {
	scp->status &= ~SWITCH_WAIT_REL;
	if (release)
	    *s = do_switch_scr(scp->sc, *s);
	else
	    scp->sc->switch_in_progress = 0;
	return 0;
    }
    return EINVAL;
}