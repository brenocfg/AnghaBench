#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pack_chain_elem {size_t size; scalar_t__ offset; scalar_t__ base_key; scalar_t__ type; } ;
struct git_pack_file {int /*<<< orphan*/  mwf; int /*<<< orphan*/  bases; } ;
typedef  int /*<<< orphan*/  git_pack_cache_entry ;
typedef  scalar_t__ git_off_t ;
typedef  scalar_t__ git_object_t ;
typedef  int /*<<< orphan*/  git_mwindow ;
struct TYPE_8__ {size_t size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_dependency_chain ;

/* Variables and functions */
 TYPE_1__ GIT_ARRAY_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ARRAY (TYPE_1__) ; 
 scalar_t__ GIT_OBJECT_OFS_DELTA ; 
 scalar_t__ GIT_OBJECT_REF_DELTA ; 
 size_t SMALL_STACK_SIZE ; 
 int /*<<< orphan*/ * cache_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ get_delta_base (struct git_pack_file*,int /*<<< orphan*/ **,scalar_t__*,scalar_t__,scalar_t__) ; 
 struct pack_chain_elem* git_array_alloc (TYPE_1__) ; 
 int /*<<< orphan*/  git_array_clear (TYPE_1__) ; 
 int /*<<< orphan*/  git_array_init_to_size (TYPE_1__,size_t) ; 
 int /*<<< orphan*/  git_mwindow_close (int /*<<< orphan*/ **) ; 
 int git_packfile_unpack_header (size_t*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct pack_chain_elem*,size_t) ; 
 int packfile_error (char*) ; 

__attribute__((used)) static int pack_dependency_chain(git_dependency_chain *chain_out,
				 git_pack_cache_entry **cached_out, git_off_t *cached_off,
				 struct pack_chain_elem *small_stack, size_t *stack_sz,
				 struct git_pack_file *p, git_off_t obj_offset)
{
	git_dependency_chain chain = GIT_ARRAY_INIT;
	git_mwindow *w_curs = NULL;
	git_off_t curpos = obj_offset, base_offset;
	int error = 0, use_heap = 0;
	size_t size, elem_pos;
	git_object_t type;

	elem_pos = 0;
	while (true) {
		struct pack_chain_elem *elem;
		git_pack_cache_entry *cached = NULL;

		/* if we have a base cached, we can stop here instead */
		if ((cached = cache_get(&p->bases, obj_offset)) != NULL) {
			*cached_out = cached;
			*cached_off = obj_offset;
			break;
		}

		/* if we run out of space on the small stack, use the array */
		if (elem_pos == SMALL_STACK_SIZE) {
			git_array_init_to_size(chain, elem_pos);
			GIT_ERROR_CHECK_ARRAY(chain);
			memcpy(chain.ptr, small_stack, elem_pos * sizeof(struct pack_chain_elem));
			chain.size = elem_pos;
			use_heap = 1;
		}

		curpos = obj_offset;
		if (!use_heap) {
			elem = &small_stack[elem_pos];
		} else {
			elem = git_array_alloc(chain);
			if (!elem) {
				error = -1;
				goto on_error;
			}
		}

		elem->base_key = obj_offset;

		error = git_packfile_unpack_header(&size, &type, &p->mwf, &w_curs, &curpos);

		if (error < 0)
			goto on_error;

		elem->offset = curpos;
		elem->size = size;
		elem->type = type;
		elem->base_key = obj_offset;

		if (type != GIT_OBJECT_OFS_DELTA && type != GIT_OBJECT_REF_DELTA)
			break;

		base_offset = get_delta_base(p, &w_curs, &curpos, type, obj_offset);
		git_mwindow_close(&w_curs);

		if (base_offset == 0) {
			error = packfile_error("delta offset is zero");
			goto on_error;
		}
		if (base_offset < 0) { /* must actually be an error code */
			error = (int)base_offset;
			goto on_error;
		}

		/* we need to pass the pos *after* the delta-base bit */
		elem->offset = curpos;

		/* go through the loop again, but with the new object */
		obj_offset = base_offset;
		elem_pos++;
	}


	*stack_sz = elem_pos + 1;
	*chain_out = chain;
	return error;

on_error:
	git_array_clear(chain);
	return error;
}