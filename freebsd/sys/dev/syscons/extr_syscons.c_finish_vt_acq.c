#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int status; TYPE_1__* sc; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_4__ {scalar_t__ switch_in_progress; TYPE_2__* new_scp; } ;

/* Variables and functions */
 int EINVAL ; 
 int SWITCH_WAIT_ACQ ; 

__attribute__((used)) static int
finish_vt_acq(scr_stat *scp)
{
    if (scp == scp->sc->new_scp && scp->status & SWITCH_WAIT_ACQ) {
	scp->status &= ~SWITCH_WAIT_ACQ;
	scp->sc->switch_in_progress = 0;
	return 0;
    }
    return EINVAL;
}