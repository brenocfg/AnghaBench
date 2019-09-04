#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hashmap_iter {int dummy; } ;
struct config_set_element {int /*<<< orphan*/  value_list; int /*<<< orphan*/ * key; } ;
struct TYPE_2__ {int /*<<< orphan*/ * items; scalar_t__ alloc; scalar_t__ nr; } ;
struct config_set {TYPE_1__ list; scalar_t__ hash_initialized; int /*<<< orphan*/  config_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hashmap_iter_init (int /*<<< orphan*/ *,struct hashmap_iter*) ; 
 struct config_set_element* hashmap_iter_next (struct hashmap_iter*) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int) ; 

void git_configset_clear(struct config_set *cs)
{
	struct config_set_element *entry;
	struct hashmap_iter iter;
	if (!cs->hash_initialized)
		return;

	hashmap_iter_init(&cs->config_hash, &iter);
	while ((entry = hashmap_iter_next(&iter))) {
		free(entry->key);
		string_list_clear(&entry->value_list, 1);
	}
	hashmap_free(&cs->config_hash, 1);
	cs->hash_initialized = 0;
	free(cs->list.items);
	cs->list.nr = 0;
	cs->list.alloc = 0;
	cs->list.items = NULL;
}