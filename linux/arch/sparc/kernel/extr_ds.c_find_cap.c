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
typedef  int u64 ;
struct ds_info {unsigned int num_ds_states; struct ds_cap_state* ds_states; } ;
struct ds_cap_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct ds_cap_state *find_cap(struct ds_info *dp, u64 handle)
{
	unsigned int index = handle >> 32;

	if (index >= dp->num_ds_states)
		return NULL;
	return &dp->ds_states[index];
}