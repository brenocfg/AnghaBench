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
struct sync_cb {int /*<<< orphan*/  flags; int /*<<< orphan*/  prefix; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  sync_submodule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sync_submodule_cb(const struct cache_entry *list_item, void *cb_data)
{
	struct sync_cb *info = cb_data;
	sync_submodule(list_item->name, info->prefix, info->flags);
}