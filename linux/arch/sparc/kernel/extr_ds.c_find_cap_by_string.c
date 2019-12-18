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
struct ds_info {int num_ds_states; struct ds_cap_state* ds_states; } ;
struct ds_cap_state {int /*<<< orphan*/  service_id; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct ds_cap_state *find_cap_by_string(struct ds_info *dp,
					       const char *name)
{
	int i;

	for (i = 0; i < dp->num_ds_states; i++) {
		if (strcmp(dp->ds_states[i].service_id, name))
			continue;

		return &dp->ds_states[i];
	}
	return NULL;
}