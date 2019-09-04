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
struct diff_queue_struct {int nr; TYPE_1__** queue; } ;
struct diff_options {int dummy; } ;
struct diff_filespec {int /*<<< orphan*/  path; int /*<<< orphan*/  oid; scalar_t__ mode; } ;
struct cache_entry {int /*<<< orphan*/  ce_flags; } ;
struct TYPE_2__ {struct diff_filespec* one; } ;

/* Variables and functions */
 int ADD_CACHE_OK_TO_ADD ; 
 int ADD_CACHE_OK_TO_REPLACE ; 
 int /*<<< orphan*/  CE_INTENT_TO_ADD ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_cache_entry (struct cache_entry*,int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 
 struct cache_entry* make_cache_entry (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_file_from_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_object_name_for_intent_to_add_entry (struct cache_entry*) ; 
 int /*<<< orphan*/  the_index ; 

__attribute__((used)) static void update_index_from_diff(struct diff_queue_struct *q,
		struct diff_options *opt, void *data)
{
	int i;
	int intent_to_add = *(int *)data;

	for (i = 0; i < q->nr; i++) {
		struct diff_filespec *one = q->queue[i]->one;
		int is_missing = !(one->mode && !is_null_oid(&one->oid));
		struct cache_entry *ce;

		if (is_missing && !intent_to_add) {
			remove_file_from_cache(one->path);
			continue;
		}

		ce = make_cache_entry(&the_index, one->mode, &one->oid, one->path,
				      0, 0);
		if (!ce)
			die(_("make_cache_entry failed for path '%s'"),
			    one->path);
		if (is_missing) {
			ce->ce_flags |= CE_INTENT_TO_ADD;
			set_object_name_for_intent_to_add_entry(ce);
		}
		add_cache_entry(ce, ADD_CACHE_OK_TO_ADD | ADD_CACHE_OK_TO_REPLACE);
	}
}