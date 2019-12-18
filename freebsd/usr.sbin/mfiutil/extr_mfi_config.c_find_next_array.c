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
typedef  scalar_t__ uint16_t ;
struct config_id_state {scalar_t__ array_ref; int array_count; scalar_t__* arrays; } ;

/* Variables and functions */

__attribute__((used)) static uint16_t
find_next_array(struct config_id_state *state)
{
	int i;

	/* Assume the current one is used. */
	state->array_ref++;

	/* Find the next free one. */
	for (i = 0; i < state->array_count; i++)
		if (state->arrays[i] == state->array_ref)
			state->array_ref++;
	return (state->array_ref);
}