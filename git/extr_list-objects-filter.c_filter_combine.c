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
struct repository {int dummy; } ;
struct oidset {int dummy; } ;
struct object {int dummy; } ;
struct combine_filter_data {size_t nr; TYPE_1__* sub; } ;
typedef  enum list_objects_filter_situation { ____Placeholder_list_objects_filter_situation } list_objects_filter_situation ;
typedef  enum list_objects_filter_result { ____Placeholder_list_objects_filter_result } list_objects_filter_result ;
struct TYPE_2__ {int /*<<< orphan*/  is_skipping_tree; } ;

/* Variables and functions */
 int LOFR_DO_SHOW ; 
 int LOFR_MARK_SEEN ; 
 int LOFR_SKIP_TREE ; 
 int process_subfilter (struct repository*,int,struct object*,char const*,char const*,TYPE_1__*) ; 

__attribute__((used)) static enum list_objects_filter_result filter_combine(
	struct repository *r,
	enum list_objects_filter_situation filter_situation,
	struct object *obj,
	const char *pathname,
	const char *filename,
	struct oidset *omits,
	void *filter_data)
{
	struct combine_filter_data *d = filter_data;
	enum list_objects_filter_result combined_result =
		LOFR_DO_SHOW | LOFR_MARK_SEEN | LOFR_SKIP_TREE;
	size_t sub;

	for (sub = 0; sub < d->nr; sub++) {
		enum list_objects_filter_result sub_result = process_subfilter(
			r, filter_situation, obj, pathname, filename,
			&d->sub[sub]);
		if (!(sub_result & LOFR_DO_SHOW))
			combined_result &= ~LOFR_DO_SHOW;
		if (!(sub_result & LOFR_MARK_SEEN))
			combined_result &= ~LOFR_MARK_SEEN;
		if (!d->sub[sub].is_skipping_tree)
			combined_result &= ~LOFR_SKIP_TREE;
	}

	return combined_result;
}