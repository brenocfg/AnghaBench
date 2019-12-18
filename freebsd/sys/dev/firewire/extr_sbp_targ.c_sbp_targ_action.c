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
typedef  union ccb {int dummy; } ccb ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbp_targ_action1 (struct cam_sim*,union ccb*) ; 
 int splfw () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
sbp_targ_action(struct cam_sim *sim, union ccb *ccb)
{
	int s;

	s = splfw();
	sbp_targ_action1(sim, ccb);
	splx(s);
}