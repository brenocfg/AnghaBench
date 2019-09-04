#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  refname; int /*<<< orphan*/  oid; } ;
struct TYPE_3__ {int nr; scalar_t__ sorted; TYPE_2__* table; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 char* name_ref_abbrev (char const*,int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 TYPE_1__ tip_table ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void add_to_tip_table(const struct object_id *oid, const char *refname,
			     int shorten_unambiguous)
{
	refname = name_ref_abbrev(refname, shorten_unambiguous);

	ALLOC_GROW(tip_table.table, tip_table.nr + 1, tip_table.alloc);
	oidcpy(&tip_table.table[tip_table.nr].oid, oid);
	tip_table.table[tip_table.nr].refname = xstrdup(refname);
	tip_table.nr++;
	tip_table.sorted = 0;
}