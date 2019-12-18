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
struct oidset {int dummy; } ;
struct object {int flags; int /*<<< orphan*/  oid; int /*<<< orphan*/  type; } ;
typedef  enum list_objects_filter_situation { ____Placeholder_list_objects_filter_situation } list_objects_filter_situation ;
typedef  enum list_objects_filter_result { ____Placeholder_list_objects_filter_result } list_objects_filter_result ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
 int LOFR_DO_SHOW ; 
 int LOFR_MARK_SEEN ; 
 int LOFR_ZERO ; 
#define  LOFS_BEGIN_TREE 130 
#define  LOFS_BLOB 129 
#define  LOFS_END_TREE 128 
 int /*<<< orphan*/  OBJ_BLOB ; 
 int /*<<< orphan*/  OBJ_TREE ; 
 int SEEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  oidset_insert (struct oidset*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum list_objects_filter_result filter_blobs_none(
	struct repository *r,
	enum list_objects_filter_situation filter_situation,
	struct object *obj,
	const char *pathname,
	const char *filename,
	struct oidset *omits,
	void *filter_data_)
{
	switch (filter_situation) {
	default:
		BUG("unknown filter_situation: %d", filter_situation);

	case LOFS_BEGIN_TREE:
		assert(obj->type == OBJ_TREE);
		/* always include all tree objects */
		return LOFR_MARK_SEEN | LOFR_DO_SHOW;

	case LOFS_END_TREE:
		assert(obj->type == OBJ_TREE);
		return LOFR_ZERO;

	case LOFS_BLOB:
		assert(obj->type == OBJ_BLOB);
		assert((obj->flags & SEEN) == 0);

		if (omits)
			oidset_insert(omits, &obj->oid);
		return LOFR_MARK_SEEN; /* but not LOFR_DO_SHOW (hard omit) */
	}
}