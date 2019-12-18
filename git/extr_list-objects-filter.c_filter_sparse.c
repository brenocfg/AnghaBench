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
struct repository {int /*<<< orphan*/  index; } ;
struct oidset {int dummy; } ;
struct object {int flags; int /*<<< orphan*/  oid; int /*<<< orphan*/  type; } ;
struct frame {int default_match; int child_prov_omit; } ;
struct filter_sparse_data {size_t nr; int /*<<< orphan*/  pl; struct frame* array_frame; int /*<<< orphan*/  alloc; } ;
typedef  enum pattern_match_result { ____Placeholder_pattern_match_result } pattern_match_result ;
typedef  enum list_objects_filter_situation { ____Placeholder_list_objects_filter_situation } list_objects_filter_situation ;
typedef  enum list_objects_filter_result { ____Placeholder_list_objects_filter_result } list_objects_filter_result ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG (char*,int) ; 
 int DT_DIR ; 
 int DT_REG ; 
 int FILTER_SHOWN_BUT_REVISIT ; 
 int LOFR_DO_SHOW ; 
 int LOFR_MARK_SEEN ; 
 int LOFR_ZERO ; 
#define  LOFS_BEGIN_TREE 130 
#define  LOFS_BLOB 129 
#define  LOFS_END_TREE 128 
 int MATCHED ; 
 int /*<<< orphan*/  OBJ_BLOB ; 
 int /*<<< orphan*/  OBJ_TREE ; 
 int SEEN ; 
 int UNDECIDED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  oidset_insert (struct oidset*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidset_remove (struct oidset*,int /*<<< orphan*/ *) ; 
 int path_matches_pattern_list (char const*,int /*<<< orphan*/ ,char const*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static enum list_objects_filter_result filter_sparse(
	struct repository *r,
	enum list_objects_filter_situation filter_situation,
	struct object *obj,
	const char *pathname,
	const char *filename,
	struct oidset *omits,
	void *filter_data_)
{
	struct filter_sparse_data *filter_data = filter_data_;
	int dtype;
	struct frame *frame;
	enum pattern_match_result match;

	switch (filter_situation) {
	default:
		BUG("unknown filter_situation: %d", filter_situation);

	case LOFS_BEGIN_TREE:
		assert(obj->type == OBJ_TREE);
		dtype = DT_DIR;
		match = path_matches_pattern_list(pathname, strlen(pathname),
						  filename, &dtype, &filter_data->pl,
						  r->index);
		if (match == UNDECIDED)
			match = filter_data->array_frame[filter_data->nr - 1].default_match;

		ALLOC_GROW(filter_data->array_frame, filter_data->nr + 1,
			   filter_data->alloc);
		filter_data->array_frame[filter_data->nr].default_match = match;
		filter_data->array_frame[filter_data->nr].child_prov_omit = 0;
		filter_data->nr++;

		/*
		 * A directory with this tree OID may appear in multiple
		 * places in the tree. (Think of a directory move or copy,
		 * with no other changes, so the OID is the same, but the
		 * full pathnames of objects within this directory are new
		 * and may match is_excluded() patterns differently.)
		 * So we cannot mark this directory as SEEN (yet), since
		 * that will prevent process_tree() from revisiting this
		 * tree object with other pathname prefixes.
		 *
		 * Only _DO_SHOW the tree object the first time we visit
		 * this tree object.
		 *
		 * We always show all tree objects.  A future optimization
		 * may want to attempt to narrow this.
		 */
		if (obj->flags & FILTER_SHOWN_BUT_REVISIT)
			return LOFR_ZERO;
		obj->flags |= FILTER_SHOWN_BUT_REVISIT;
		return LOFR_DO_SHOW;

	case LOFS_END_TREE:
		assert(obj->type == OBJ_TREE);
		assert(filter_data->nr > 1);

		frame = &filter_data->array_frame[--filter_data->nr];

		/*
		 * Tell our parent directory if any of our children were
		 * provisionally omitted.
		 */
		filter_data->array_frame[filter_data->nr - 1].child_prov_omit |=
			frame->child_prov_omit;

		/*
		 * If there are NO provisionally omitted child objects (ALL child
		 * objects in this folder were INCLUDED), then we can mark the
		 * folder as SEEN (so we will not have to revisit it again).
		 */
		if (!frame->child_prov_omit)
			return LOFR_MARK_SEEN;
		return LOFR_ZERO;

	case LOFS_BLOB:
		assert(obj->type == OBJ_BLOB);
		assert((obj->flags & SEEN) == 0);

		frame = &filter_data->array_frame[filter_data->nr - 1];

		dtype = DT_REG;
		match = path_matches_pattern_list(pathname, strlen(pathname),
					    filename, &dtype, &filter_data->pl,
					    r->index);
		if (match == UNDECIDED)
			match = frame->default_match;
		if (match == MATCHED) {
			if (omits)
				oidset_remove(omits, &obj->oid);
			return LOFR_MARK_SEEN | LOFR_DO_SHOW;
		}

		/*
		 * Provisionally omit it.  We've already established that
		 * this pathname is not in the sparse-checkout specification
		 * with the CURRENT pathname, so we *WANT* to omit this blob.
		 *
		 * However, a pathname elsewhere in the tree may also
		 * reference this same blob, so we cannot reject it yet.
		 * Leave the LOFR_ bits unset so that if the blob appears
		 * again in the traversal, we will be asked again.
		 */
		if (omits)
			oidset_insert(omits, &obj->oid);

		/*
		 * Remember that at least 1 blob in this tree was
		 * provisionally omitted.  This prevents us from short
		 * cutting the tree in future iterations.
		 */
		frame->child_prov_omit = 1;
		return LOFR_ZERO;
	}
}