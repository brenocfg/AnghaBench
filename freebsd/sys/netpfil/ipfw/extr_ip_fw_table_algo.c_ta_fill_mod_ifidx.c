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
typedef  scalar_t__ uint64_t ;
struct table_info {int dummy; } ;
struct mod_item {scalar_t__ size; int /*<<< orphan*/  main_ptr; } ;
struct iftable_cfg {scalar_t__ size; int used; int /*<<< orphan*/  main_ptr; } ;
struct ifidx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ta_fill_mod_ifidx(void *ta_state, struct table_info *ti, void *ta_buf,
    uint64_t *pflags)
{
	struct mod_item *mi;
	struct iftable_cfg *icfg;

	mi = (struct mod_item *)ta_buf;
	icfg = (struct iftable_cfg *)ta_state;

	/* Check if we still need to grow array */
	if (icfg->size >= mi->size) {
		*pflags = 0;
		return (0);
	}

	memcpy(mi->main_ptr, icfg->main_ptr, icfg->used * sizeof(struct ifidx));

	return (0);
}