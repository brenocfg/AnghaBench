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
typedef  scalar_t__ u16 ;
struct mlx5_core_diagnostics_entry {scalar_t__ counter_id; } ;

/* Variables and functions */

__attribute__((used)) static int mlx5_core_get_index_of_diag_counter(
	const struct mlx5_core_diagnostics_entry *entry,
	int size, u16 counter_id)
{
	int x;

	/* check for invalid counter ID */
	if (counter_id == 0)
		return -1;

	/* lookup counter ID in table */
	for (x = 0; x != size; x++) {
		if (entry[x].counter_id == counter_id)
			return x;
	}
	return -1;
}