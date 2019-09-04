#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int ha; int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_6__ xrecord_t ;
typedef  int /*<<< orphan*/  xpparam_t ;
struct hashmap {int alloc; int has_matches; int /*<<< orphan*/  nr; TYPE_5__* entries; TYPE_5__* last; TYPE_5__* first; TYPE_4__* env; TYPE_2__* xpp; } ;
struct TYPE_11__ {int line1; int hash; int line2; struct TYPE_11__* previous; struct TYPE_11__* next; int /*<<< orphan*/  anchor; } ;
struct TYPE_9__ {TYPE_6__** recs; } ;
struct TYPE_7__ {TYPE_6__** recs; } ;
struct TYPE_10__ {TYPE_3__ xdf1; TYPE_1__ xdf2; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int NON_UNIQUE ; 
 int /*<<< orphan*/  is_anchor (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdl_recmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void insert_record(xpparam_t const *xpp, int line, struct hashmap *map,
			  int pass)
{
	xrecord_t **records = pass == 1 ?
		map->env->xdf1.recs : map->env->xdf2.recs;
	xrecord_t *record = records[line - 1], *other;
	/*
	 * After xdl_prepare_env() (or more precisely, due to
	 * xdl_classify_record()), the "ha" member of the records (AKA lines)
	 * is _not_ the hash anymore, but a linearized version of it.  In
	 * other words, the "ha" member is guaranteed to start with 0 and
	 * the second record's ha can only be 0 or 1, etc.
	 *
	 * So we multiply ha by 2 in the hope that the hashing was
	 * "unique enough".
	 */
	int index = (int)((record->ha << 1) % map->alloc);

	while (map->entries[index].line1) {
		other = map->env->xdf1.recs[map->entries[index].line1 - 1];
		if (map->entries[index].hash != record->ha ||
				!xdl_recmatch(record->ptr, record->size,
					other->ptr, other->size,
					map->xpp->flags)) {
			if (++index >= map->alloc)
				index = 0;
			continue;
		}
		if (pass == 2)
			map->has_matches = 1;
		if (pass == 1 || map->entries[index].line2)
			map->entries[index].line2 = NON_UNIQUE;
		else
			map->entries[index].line2 = line;
		return;
	}
	if (pass == 2)
		return;
	map->entries[index].line1 = line;
	map->entries[index].hash = record->ha;
	map->entries[index].anchor = is_anchor(xpp, map->env->xdf1.recs[line - 1]->ptr);
	if (!map->first)
		map->first = map->entries + index;
	if (map->last) {
		map->last->next = map->entries + index;
		map->entries[index].previous = map->last;
	}
	map->last = map->entries + index;
	map->nr++;
}