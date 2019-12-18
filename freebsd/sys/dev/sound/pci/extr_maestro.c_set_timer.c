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
typedef  int u_int ;
struct agg_info {int playchns; int active; int /*<<< orphan*/  rch; scalar_t__ pch; } ;

/* Variables and functions */
 int calc_timer_div (scalar_t__) ; 
 int calc_timer_div_rch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wp_settimer (struct agg_info*,int) ; 

__attribute__((used)) static void
set_timer(struct agg_info *ess)
{
	int i;
	u_int	dv = 32 << 7, newdv;

	for (i = 0; i < ess->playchns; i++)
		if ((ess->active & (1 << i)) &&
		    (dv > (newdv = calc_timer_div(ess->pch + i))))
			dv = newdv;
	if ((ess->active & (1 << i)) &&
	    (dv > (newdv = calc_timer_div_rch(&ess->rch))))
		dv = newdv;

	wp_settimer(ess, dv);
}