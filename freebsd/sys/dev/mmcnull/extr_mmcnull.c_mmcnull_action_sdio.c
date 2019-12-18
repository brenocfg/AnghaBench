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
 int /*<<< orphan*/  mmcnull_action_sd (struct cam_sim*,union ccb*) ; 

__attribute__((used)) static void
mmcnull_action_sdio(struct cam_sim *sim, union ccb *ccb) {
	mmcnull_action_sd(sim, ccb);
}