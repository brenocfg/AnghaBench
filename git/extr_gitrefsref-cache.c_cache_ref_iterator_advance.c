#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ref_iterator {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct TYPE_5__ {TYPE_1__ value; } ;
struct ref_entry {int flag; TYPE_2__ u; int /*<<< orphan*/  name; } ;
struct ref_dir {int nr; struct ref_entry** entries; } ;
struct cache_ref_iterator_level {int index; scalar_t__ prefix_state; struct ref_dir* dir; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/ * oid; int /*<<< orphan*/  refname; } ;
struct cache_ref_iterator {int levels_nr; TYPE_3__ base; struct cache_ref_iterator_level* levels; int /*<<< orphan*/  levels_alloc; int /*<<< orphan*/  prefix; } ;
typedef  enum prefix_state { ____Placeholder_prefix_state } prefix_state ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct cache_ref_iterator_level*,int,int /*<<< orphan*/ ) ; 
 int ITER_OK ; 
 int PREFIX_EXCLUDES_DIR ; 
 scalar_t__ PREFIX_WITHIN_DIR ; 
 int REF_DIR ; 
 struct ref_dir* get_ref_dir (struct ref_entry*) ; 
 int overlaps_prefix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ref_iterator_abort (struct ref_iterator*) ; 
 int /*<<< orphan*/  sort_ref_dir (struct ref_dir*) ; 

__attribute__((used)) static int cache_ref_iterator_advance(struct ref_iterator *ref_iterator)
{
	struct cache_ref_iterator *iter =
		(struct cache_ref_iterator *)ref_iterator;

	while (1) {
		struct cache_ref_iterator_level *level =
			&iter->levels[iter->levels_nr - 1];
		struct ref_dir *dir = level->dir;
		struct ref_entry *entry;
		enum prefix_state entry_prefix_state;

		if (level->index == -1)
			sort_ref_dir(dir);

		if (++level->index == level->dir->nr) {
			/* This level is exhausted; pop up a level */
			if (--iter->levels_nr == 0)
				return ref_iterator_abort(ref_iterator);

			continue;
		}

		entry = dir->entries[level->index];

		if (level->prefix_state == PREFIX_WITHIN_DIR) {
			entry_prefix_state = overlaps_prefix(entry->name, iter->prefix);
			if (entry_prefix_state == PREFIX_EXCLUDES_DIR)
				continue;
		} else {
			entry_prefix_state = level->prefix_state;
		}

		if (entry->flag & REF_DIR) {
			/* push down a level */
			ALLOC_GROW(iter->levels, iter->levels_nr + 1,
				   iter->levels_alloc);

			level = &iter->levels[iter->levels_nr++];
			level->dir = get_ref_dir(entry);
			level->prefix_state = entry_prefix_state;
			level->index = -1;
		} else {
			iter->base.refname = entry->name;
			iter->base.oid = &entry->u.value.oid;
			iter->base.flags = entry->flag;
			return ITER_OK;
		}
	}
}