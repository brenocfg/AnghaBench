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
struct subfilter {int is_skipping_tree; int /*<<< orphan*/  skip_tree; int /*<<< orphan*/  seen; int /*<<< orphan*/  filter; } ;
struct repository {int dummy; } ;
struct object {int /*<<< orphan*/  oid; } ;
typedef  enum list_objects_filter_situation { ____Placeholder_list_objects_filter_situation } list_objects_filter_situation ;
typedef  enum list_objects_filter_result { ____Placeholder_list_objects_filter_result } list_objects_filter_result ;

/* Variables and functions */
 int LOFR_MARK_SEEN ; 
 int LOFR_SKIP_TREE ; 
 int LOFR_ZERO ; 
 int LOFS_END_TREE ; 
 int list_objects_filter__filter_object (struct repository*,int,struct object*,char const*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ oidset_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidset_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum list_objects_filter_result process_subfilter(
	struct repository *r,
	enum list_objects_filter_situation filter_situation,
	struct object *obj,
	const char *pathname,
	const char *filename,
	struct subfilter *sub)
{
	enum list_objects_filter_result result;

	/*
	 * Check and update is_skipping_tree before oidset_contains so
	 * that is_skipping_tree gets unset even when the object is
	 * marked as seen.  As of this writing, no filter uses
	 * LOFR_MARK_SEEN on trees that also uses LOFR_SKIP_TREE, so the
	 * ordering is only theoretically important. Be cautious if you
	 * change the order of the below checks and more filters have
	 * been added!
	 */
	if (sub->is_skipping_tree) {
		if (filter_situation == LOFS_END_TREE &&
		    oideq(&obj->oid, &sub->skip_tree))
			sub->is_skipping_tree = 0;
		else
			return LOFR_ZERO;
	}
	if (oidset_contains(&sub->seen, &obj->oid))
		return LOFR_ZERO;

	result = list_objects_filter__filter_object(
		r, filter_situation, obj, pathname, filename, sub->filter);

	if (result & LOFR_MARK_SEEN)
		oidset_insert(&sub->seen, &obj->oid);

	if (result & LOFR_SKIP_TREE) {
		sub->is_skipping_tree = 1;
		sub->skip_tree = obj->oid;
	}

	return result;
}