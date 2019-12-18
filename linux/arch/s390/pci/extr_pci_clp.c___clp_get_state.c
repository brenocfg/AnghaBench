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
struct clp_state_data {scalar_t__ fid; int /*<<< orphan*/  state; } ;
struct clp_fh_list_entry {scalar_t__ fid; int /*<<< orphan*/  config_state; } ;

/* Variables and functions */

__attribute__((used)) static void __clp_get_state(struct clp_fh_list_entry *entry, void *data)
{
	struct clp_state_data *sd = data;

	if (entry->fid != sd->fid)
		return;

	sd->state = entry->config_state;
}