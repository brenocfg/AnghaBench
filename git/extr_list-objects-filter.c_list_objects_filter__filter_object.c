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
struct repository {int dummy; } ;
struct object {int flags; } ;
struct filter {int (* filter_object_fn ) (struct repository*,int,struct object*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  filter_data; int /*<<< orphan*/  omits; } ;
typedef  enum list_objects_filter_situation { ____Placeholder_list_objects_filter_situation } list_objects_filter_situation ;
typedef  enum list_objects_filter_result { ____Placeholder_list_objects_filter_result } list_objects_filter_result ;

/* Variables and functions */
 int LOFR_DO_SHOW ; 
 int LOFR_MARK_SEEN ; 
 int LOFS_END_TREE ; 
 int NOT_USER_GIVEN ; 
 int stub1 (struct repository*,int,struct object*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum list_objects_filter_result list_objects_filter__filter_object(
	struct repository *r,
	enum list_objects_filter_situation filter_situation,
	struct object *obj,
	const char *pathname,
	const char *filename,
	struct filter *filter)
{
	if (filter && (obj->flags & NOT_USER_GIVEN))
		return filter->filter_object_fn(r, filter_situation, obj,
						pathname, filename,
						filter->omits,
						filter->filter_data);
	/*
	 * No filter is active or user gave object explicitly. In this case,
	 * always show the object (except when LOFS_END_TREE, since this tree
	 * had already been shown when LOFS_BEGIN_TREE).
	 */
	if (filter_situation == LOFS_END_TREE)
		return 0;
	return LOFR_MARK_SEEN | LOFR_DO_SHOW;
}