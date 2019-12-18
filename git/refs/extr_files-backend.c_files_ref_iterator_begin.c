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
struct ref_store {int dummy; } ;
struct ref_iterator {int /*<<< orphan*/  ordered; } ;
struct files_ref_store {int /*<<< orphan*/  packed_ref_store; } ;
struct files_ref_iterator {unsigned int flags; struct ref_iterator* iter0; struct ref_iterator base; } ;

/* Variables and functions */
 unsigned int DO_FOR_EACH_INCLUDE_BROKEN ; 
 unsigned int REF_STORE_ODB ; 
 unsigned int REF_STORE_READ ; 
 int /*<<< orphan*/  base_ref_iterator_init (struct ref_iterator*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ref_iterator* cache_ref_iterator_begin (int /*<<< orphan*/ ,char const*,int) ; 
 struct files_ref_store* files_downcast (struct ref_store*,unsigned int,char*) ; 
 int /*<<< orphan*/  files_ref_iterator_vtable ; 
 int /*<<< orphan*/  get_loose_ref_cache (struct files_ref_store*) ; 
 struct ref_iterator* overlay_ref_iterator_begin (struct ref_iterator*,struct ref_iterator*) ; 
 struct ref_iterator* refs_ref_iterator_begin (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,unsigned int) ; 
 struct files_ref_iterator* xcalloc (int,int) ; 

__attribute__((used)) static struct ref_iterator *files_ref_iterator_begin(
		struct ref_store *ref_store,
		const char *prefix, unsigned int flags)
{
	struct files_ref_store *refs;
	struct ref_iterator *loose_iter, *packed_iter, *overlay_iter;
	struct files_ref_iterator *iter;
	struct ref_iterator *ref_iterator;
	unsigned int required_flags = REF_STORE_READ;

	if (!(flags & DO_FOR_EACH_INCLUDE_BROKEN))
		required_flags |= REF_STORE_ODB;

	refs = files_downcast(ref_store, required_flags, "ref_iterator_begin");

	/*
	 * We must make sure that all loose refs are read before
	 * accessing the packed-refs file; this avoids a race
	 * condition if loose refs are migrated to the packed-refs
	 * file by a simultaneous process, but our in-memory view is
	 * from before the migration. We ensure this as follows:
	 * First, we call start the loose refs iteration with its
	 * `prime_ref` argument set to true. This causes the loose
	 * references in the subtree to be pre-read into the cache.
	 * (If they've already been read, that's OK; we only need to
	 * guarantee that they're read before the packed refs, not
	 * *how much* before.) After that, we call
	 * packed_ref_iterator_begin(), which internally checks
	 * whether the packed-ref cache is up to date with what is on
	 * disk, and re-reads it if not.
	 */

	loose_iter = cache_ref_iterator_begin(get_loose_ref_cache(refs),
					      prefix, 1);

	/*
	 * The packed-refs file might contain broken references, for
	 * example an old version of a reference that points at an
	 * object that has since been garbage-collected. This is OK as
	 * long as there is a corresponding loose reference that
	 * overrides it, and we don't want to emit an error message in
	 * this case. So ask the packed_ref_store for all of its
	 * references, and (if needed) do our own check for broken
	 * ones in files_ref_iterator_advance(), after we have merged
	 * the packed and loose references.
	 */
	packed_iter = refs_ref_iterator_begin(
			refs->packed_ref_store, prefix, 0,
			DO_FOR_EACH_INCLUDE_BROKEN);

	overlay_iter = overlay_ref_iterator_begin(loose_iter, packed_iter);

	iter = xcalloc(1, sizeof(*iter));
	ref_iterator = &iter->base;
	base_ref_iterator_init(ref_iterator, &files_ref_iterator_vtable,
			       overlay_iter->ordered);
	iter->iter0 = overlay_iter;
	iter->flags = flags;

	return ref_iterator;
}