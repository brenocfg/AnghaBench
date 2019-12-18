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
struct ds_info {int num_ds_states; struct ds_cap_state* ds_states; scalar_t__ hs_state; } ;
struct ds_cap_state {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_STATE_UNKNOWN ; 

__attribute__((used)) static void ds_reset(struct ds_info *dp)
{
	int i;

	dp->hs_state = 0;

	for (i = 0; i < dp->num_ds_states; i++) {
		struct ds_cap_state *cp = &dp->ds_states[i];

		cp->state = CAP_STATE_UNKNOWN;
	}
}