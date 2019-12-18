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
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct seen_map_entry {scalar_t__ depth; TYPE_1__ base; } ;
struct repository {int dummy; } ;
struct oidset {int dummy; } ;
struct object {int /*<<< orphan*/  oid; int /*<<< orphan*/  type; } ;
struct filter_trees_depth_data {scalar_t__ current_depth; scalar_t__ exclude_depth; int /*<<< orphan*/  seen_at_depth; } ;
typedef  enum list_objects_filter_situation { ____Placeholder_list_objects_filter_situation } list_objects_filter_situation ;
typedef  enum list_objects_filter_result { ____Placeholder_list_objects_filter_result } list_objects_filter_result ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
 int LOFR_DO_SHOW ; 
 int LOFR_MARK_SEEN ; 
 int LOFR_SKIP_TREE ; 
 int LOFR_ZERO ; 
#define  LOFS_BEGIN_TREE 130 
#define  LOFS_BLOB 129 
#define  LOFS_END_TREE 128 
 int /*<<< orphan*/  OBJ_TREE ; 
 int /*<<< orphan*/  assert (int) ; 
 int filter_trees_update_omits (struct object*,struct oidset*,int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct seen_map_entry* oidmap_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidmap_put (int /*<<< orphan*/ *,struct seen_map_entry*) ; 
 struct seen_map_entry* xcalloc (int,int) ; 

__attribute__((used)) static enum list_objects_filter_result filter_trees_depth(
	struct repository *r,
	enum list_objects_filter_situation filter_situation,
	struct object *obj,
	const char *pathname,
	const char *filename,
	struct oidset *omits,
	void *filter_data_)
{
	struct filter_trees_depth_data *filter_data = filter_data_;
	struct seen_map_entry *seen_info;
	int include_it = filter_data->current_depth <
		filter_data->exclude_depth;
	int filter_res;
	int already_seen;

	/*
	 * Note that we do not use _MARK_SEEN in order to allow re-traversal in
	 * case we encounter a tree or blob again at a shallower depth.
	 */

	switch (filter_situation) {
	default:
		BUG("unknown filter_situation: %d", filter_situation);

	case LOFS_END_TREE:
		assert(obj->type == OBJ_TREE);
		filter_data->current_depth--;
		return LOFR_ZERO;

	case LOFS_BLOB:
		filter_trees_update_omits(obj, omits, include_it);
		return include_it ? LOFR_MARK_SEEN | LOFR_DO_SHOW : LOFR_ZERO;

	case LOFS_BEGIN_TREE:
		seen_info = oidmap_get(
			&filter_data->seen_at_depth, &obj->oid);
		if (!seen_info) {
			seen_info = xcalloc(1, sizeof(*seen_info));
			oidcpy(&seen_info->base.oid, &obj->oid);
			seen_info->depth = filter_data->current_depth;
			oidmap_put(&filter_data->seen_at_depth, seen_info);
			already_seen = 0;
		} else {
			already_seen =
				filter_data->current_depth >= seen_info->depth;
		}

		if (already_seen) {
			filter_res = LOFR_SKIP_TREE;
		} else {
			int been_omitted = filter_trees_update_omits(
				obj, omits, include_it);
			seen_info->depth = filter_data->current_depth;

			if (include_it)
				filter_res = LOFR_DO_SHOW;
			else if (omits && !been_omitted)
				/*
				 * Must update omit information of children
				 * recursively; they have not been omitted yet.
				 */
				filter_res = LOFR_ZERO;
			else
				filter_res = LOFR_SKIP_TREE;
		}

		filter_data->current_depth++;
		return filter_res;
	}
}