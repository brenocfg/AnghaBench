#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct interface {int dummy; } ;
struct dr {scalar_t__ dr_life; scalar_t__ dr_ts; scalar_t__ dr_recv_pref; struct interface* dr_ifp; } ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 size_t MAX_ADS ; 
 struct dr* drs ; 
 TYPE_1__ rdisc_timer ; 

void
if_bad_rdisc(struct interface *ifp)
{
	struct dr *drp;

	for (drp = drs; drp < &drs[MAX_ADS]; drp++) {
		if (drp->dr_ifp != ifp)
			continue;
		drp->dr_recv_pref = 0;
		drp->dr_ts = 0;
		drp->dr_life = 0;
	}

	/* make a note to re-solicit, turn RIP on or off, etc. */
	rdisc_timer.tv_sec = 0;
}