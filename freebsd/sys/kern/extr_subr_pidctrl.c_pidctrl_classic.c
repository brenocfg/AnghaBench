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
struct pidctrl {int pc_setpoint; int pc_olderror; int pc_error; int pc_integral; int pc_bound; int pc_derivative; int pc_output; int pc_input; int /*<<< orphan*/  pc_Kdd; int /*<<< orphan*/  pc_Kid; int /*<<< orphan*/  pc_Kpd; int /*<<< orphan*/  pc_ticks; } ;

/* Variables and functions */
 void* MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  ticks ; 

int
pidctrl_classic(struct pidctrl *pc, int input)
{
	int output, error;
	int Kpd, Kid, Kdd;

	error = pc->pc_setpoint - input;
	pc->pc_ticks = ticks;
	pc->pc_olderror = pc->pc_error;

	/* Fetch gains and prevent divide by zero. */
	Kpd = MAX(pc->pc_Kpd, 1);
	Kid = MAX(pc->pc_Kid, 1);
	Kdd = MAX(pc->pc_Kdd, 1);

	/* Compute P (proportional error), I (integral), D (derivative). */
	pc->pc_error = error;
	pc->pc_integral =
	    MAX(MIN(pc->pc_integral + error, pc->pc_bound), -pc->pc_bound);
	pc->pc_derivative = error - pc->pc_olderror;

	/* Divide by inverse gain values to produce output. */
	output = (pc->pc_error / Kpd) + (pc->pc_integral / Kid) +
	    (pc->pc_derivative / Kdd);
	/* Save for sysctl. */
	pc->pc_output = output;
	pc->pc_input = input;

	return (output);
}