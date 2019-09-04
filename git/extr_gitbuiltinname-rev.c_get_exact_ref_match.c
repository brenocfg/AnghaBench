#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hash; } ;
struct object {TYPE_1__ oid; } ;
struct TYPE_7__ {char const* refname; } ;
struct TYPE_6__ {int sorted; TYPE_3__* table; int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSORT (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nth_tip_table_ent ; 
 int sha1_pos (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ tip_table ; 
 int /*<<< orphan*/  tipcmp ; 

__attribute__((used)) static const char *get_exact_ref_match(const struct object *o)
{
	int found;

	if (!tip_table.table || !tip_table.nr)
		return NULL;

	if (!tip_table.sorted) {
		QSORT(tip_table.table, tip_table.nr, tipcmp);
		tip_table.sorted = 1;
	}

	found = sha1_pos(o->oid.hash, tip_table.table, tip_table.nr,
			 nth_tip_table_ent);
	if (0 <= found)
		return tip_table.table[found].refname;
	return NULL;
}