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
struct TYPE_3__ {int nr; struct object_array_entry* objects; } ;
struct rev_info {int /*<<< orphan*/  diffopt; TYPE_1__ pending; } ;
struct object_array_entry {int /*<<< orphan*/  name; TYPE_2__* item; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ diff_cache (struct rev_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  diff_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_set_mnemonic_prefix (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  diffcore_fix_diff_index () ; 
 int /*<<< orphan*/  diffcore_std (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  trace_performance_enter () ; 
 int /*<<< orphan*/  trace_performance_leave (char*) ; 

int run_diff_index(struct rev_info *revs, int cached)
{
	struct object_array_entry *ent;

	if (revs->pending.nr != 1)
		BUG("run_diff_index must be passed exactly one tree");

	trace_performance_enter();
	ent = revs->pending.objects;
	if (diff_cache(revs, &ent->item->oid, ent->name, cached))
		exit(128);

	diff_set_mnemonic_prefix(&revs->diffopt, "c/", cached ? "i/" : "w/");
	diffcore_fix_diff_index();
	diffcore_std(&revs->diffopt);
	diff_flush(&revs->diffopt);
	trace_performance_leave("diff-index");
	return 0;
}