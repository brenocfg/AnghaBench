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
struct pidctrl {int pc_setpoint; int pc_interval; int pc_bound; int pc_Kpd; int pc_Kid; int pc_Kdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct pidctrl*,int) ; 

void
pidctrl_init(struct pidctrl *pc, int interval, int setpoint, int bound,
    int Kpd, int Kid, int Kdd)
{

	bzero(pc, sizeof(*pc));
	pc->pc_setpoint = setpoint;
	pc->pc_interval = interval;
	pc->pc_bound = bound * setpoint * Kid;
	pc->pc_Kpd = Kpd;
	pc->pc_Kid = Kid;
	pc->pc_Kdd = Kdd;
}