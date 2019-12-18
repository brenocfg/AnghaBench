#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct unpacked {size_t depth; void* data; int /*<<< orphan*/  index; TYPE_1__* object; } ;
struct TYPE_7__ {scalar_t__ type; size_t size; size_t delta_size; void* delta_data; struct TYPE_7__* delta; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_pobject ;
struct TYPE_8__ {size_t delta_cache_size; int /*<<< orphan*/  odb; } ;
typedef  TYPE_2__ git_packbuilder ;
typedef  int /*<<< orphan*/  git_odb_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (void*) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ delta_cacheable (TYPE_2__*,size_t,size_t,size_t) ; 
 int git__add_sizet_overflow (size_t*,size_t,size_t) ; 
 int /*<<< orphan*/  git__free (void*) ; 
 int /*<<< orphan*/  git__is_ulong (size_t) ; 
 void* git__malloc (size_t) ; 
 void* git__realloc (void*,size_t) ; 
 scalar_t__ git_delta_create_from_index (void**,size_t*,int /*<<< orphan*/ ,void*,size_t,size_t) ; 
 scalar_t__ git_delta_index_init (int /*<<< orphan*/ *,void*,size_t) ; 
 scalar_t__ git_delta_index_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_odb_object_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 size_t git_odb_object_size (int /*<<< orphan*/ *) ; 
 scalar_t__ git_odb_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_packbuilder__cache_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  git_packbuilder__cache_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int try_delta(git_packbuilder *pb, struct unpacked *trg,
		     struct unpacked *src, size_t max_depth,
			 size_t *mem_usage, int *ret)
{
	git_pobject *trg_object = trg->object;
	git_pobject *src_object = src->object;
	git_odb_object *obj;
	size_t trg_size, src_size, delta_size, sizediff, max_size, sz;
	size_t ref_depth;
	void *delta_buf;

	/* Don't bother doing diffs between different types */
	if (trg_object->type != src_object->type) {
		*ret = -1;
		return 0;
	}

	*ret = 0;

	/* TODO: support reuse-delta */

	/* Let's not bust the allowed depth. */
	if (src->depth >= max_depth)
		return 0;

	/* Now some size filtering heuristics. */
	trg_size = trg_object->size;
	if (!trg_object->delta) {
		max_size = trg_size/2 - 20;
		ref_depth = 1;
	} else {
		max_size = trg_object->delta_size;
		ref_depth = trg->depth;
	}

	max_size = (uint64_t)max_size * (max_depth - src->depth) /
					(max_depth - ref_depth + 1);
	if (max_size == 0)
		return 0;

	src_size = src_object->size;
	sizediff = src_size < trg_size ? trg_size - src_size : 0;
	if (sizediff >= max_size)
		return 0;
	if (trg_size < src_size / 32)
		return 0;

	/* Load data if not already done */
	if (!trg->data) {
		if (git_odb_read(&obj, pb->odb, &trg_object->id) < 0)
			return -1;

		sz = git_odb_object_size(obj);
		trg->data = git__malloc(sz);
		GIT_ERROR_CHECK_ALLOC(trg->data);
		memcpy(trg->data, git_odb_object_data(obj), sz);

		git_odb_object_free(obj);

		if (sz != trg_size) {
			git_error_set(GIT_ERROR_INVALID,
				   "inconsistent target object length");
			return -1;
		}

		*mem_usage += sz;
	}
	if (!src->data) {
		size_t obj_sz;

		if (git_odb_read(&obj, pb->odb, &src_object->id) < 0 ||
			!git__is_ulong(obj_sz = git_odb_object_size(obj)))
			return -1;

		sz = obj_sz;
		src->data = git__malloc(sz);
		GIT_ERROR_CHECK_ALLOC(src->data);
		memcpy(src->data, git_odb_object_data(obj), sz);

		git_odb_object_free(obj);

		if (sz != src_size) {
			git_error_set(GIT_ERROR_INVALID,
				   "inconsistent source object length");
			return -1;
		}

		*mem_usage += sz;
	}
	if (!src->index) {
		if (git_delta_index_init(&src->index, src->data, src_size) < 0)
			return 0; /* suboptimal pack - out of memory */

		*mem_usage += git_delta_index_size(src->index);
	}

	if (git_delta_create_from_index(&delta_buf, &delta_size, src->index, trg->data, trg_size,
		max_size) < 0)
		return 0;

	if (trg_object->delta) {
		/* Prefer only shallower same-sized deltas. */
		if (delta_size == trg_object->delta_size &&
		    src->depth + 1 >= trg->depth) {
			git__free(delta_buf);
			return 0;
		}
	}

	git_packbuilder__cache_lock(pb);
	if (trg_object->delta_data) {
		git__free(trg_object->delta_data);
		assert(pb->delta_cache_size >= trg_object->delta_size);
		pb->delta_cache_size -= trg_object->delta_size;
		trg_object->delta_data = NULL;
	}
	if (delta_cacheable(pb, src_size, trg_size, delta_size)) {
		bool overflow = git__add_sizet_overflow(
			&pb->delta_cache_size, pb->delta_cache_size, delta_size);

		git_packbuilder__cache_unlock(pb);

		if (overflow) {
			git__free(delta_buf);
			return -1;
		}

		trg_object->delta_data = git__realloc(delta_buf, delta_size);
		GIT_ERROR_CHECK_ALLOC(trg_object->delta_data);
	} else {
		/* create delta when writing the pack */
		git_packbuilder__cache_unlock(pb);
		git__free(delta_buf);
	}

	trg_object->delta = src_object;
	trg_object->delta_size = delta_size;
	trg->depth = src->depth + 1;

	*ret = 1;
	return 0;
}