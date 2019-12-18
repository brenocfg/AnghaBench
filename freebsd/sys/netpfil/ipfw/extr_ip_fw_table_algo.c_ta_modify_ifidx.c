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
typedef  int /*<<< orphan*/  uint64_t ;
struct table_info {void* state; } ;
struct mod_item {void* main_ptr; int /*<<< orphan*/  size; } ;
struct iftable_cfg {void* main_ptr; int /*<<< orphan*/  size; } ;

/* Variables and functions */

__attribute__((used)) static void
ta_modify_ifidx(void *ta_state, struct table_info *ti, void *ta_buf,
    uint64_t pflags)
{
	struct mod_item *mi;
	struct iftable_cfg *icfg;
	void *old_ptr;

	mi = (struct mod_item *)ta_buf;
	icfg = (struct iftable_cfg *)ta_state;

	old_ptr = icfg->main_ptr;
	icfg->main_ptr = mi->main_ptr;
	icfg->size = mi->size;
	ti->state = icfg->main_ptr;

	mi->main_ptr = old_ptr;
}