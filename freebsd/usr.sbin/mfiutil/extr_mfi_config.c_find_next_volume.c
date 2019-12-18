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
typedef  scalar_t__ uint8_t ;
struct config_id_state {scalar_t__ target_id; int log_drv_count; scalar_t__* volumes; } ;

/* Variables and functions */

__attribute__((used)) static uint8_t
find_next_volume(struct config_id_state *state)
{
	int i;

	/* Assume the current one is used. */
	state->target_id++;

	/* Find the next free one. */
	for (i = 0; i < state->log_drv_count; i++)
		if (state->volumes[i] == state->target_id)
			state->target_id++;
	return (state->target_id);
}