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
struct snapshot {char* start; char const* eof; } ;
struct ref_store {int dummy; } ;
struct ref_iterator {int /*<<< orphan*/ * oid; } ;
struct packed_ref_store {int dummy; } ;
struct packed_ref_iterator {char const* pos; char const* eof; unsigned int flags; int /*<<< orphan*/  oid; struct ref_iterator base; int /*<<< orphan*/  refname_buf; struct snapshot* snapshot; } ;

/* Variables and functions */
 unsigned int DO_FOR_EACH_INCLUDE_BROKEN ; 
 unsigned int REF_STORE_ODB ; 
 unsigned int REF_STORE_READ ; 
 int /*<<< orphan*/  acquire_snapshot (struct snapshot*) ; 
 int /*<<< orphan*/  base_ref_iterator_init (struct ref_iterator*,int /*<<< orphan*/ *,int) ; 
 struct ref_iterator* empty_ref_iterator_begin () ; 
 char* find_reference_location (struct snapshot*,char const*,int /*<<< orphan*/ ) ; 
 struct snapshot* get_snapshot (struct packed_ref_store*) ; 
 struct packed_ref_store* packed_downcast (struct ref_store*,unsigned int,char*) ; 
 int /*<<< orphan*/  packed_ref_iterator_vtable ; 
 struct ref_iterator* prefix_ref_iterator_begin (struct ref_iterator*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct packed_ref_iterator* xcalloc (int,int) ; 

__attribute__((used)) static struct ref_iterator *packed_ref_iterator_begin(
		struct ref_store *ref_store,
		const char *prefix, unsigned int flags)
{
	struct packed_ref_store *refs;
	struct snapshot *snapshot;
	const char *start;
	struct packed_ref_iterator *iter;
	struct ref_iterator *ref_iterator;
	unsigned int required_flags = REF_STORE_READ;

	if (!(flags & DO_FOR_EACH_INCLUDE_BROKEN))
		required_flags |= REF_STORE_ODB;
	refs = packed_downcast(ref_store, required_flags, "ref_iterator_begin");

	/*
	 * Note that `get_snapshot()` internally checks whether the
	 * snapshot is up to date with what is on disk, and re-reads
	 * it if not.
	 */
	snapshot = get_snapshot(refs);

	if (prefix && *prefix)
		start = find_reference_location(snapshot, prefix, 0);
	else
		start = snapshot->start;

	if (start == snapshot->eof)
		return empty_ref_iterator_begin();

	iter = xcalloc(1, sizeof(*iter));
	ref_iterator = &iter->base;
	base_ref_iterator_init(ref_iterator, &packed_ref_iterator_vtable, 1);

	iter->snapshot = snapshot;
	acquire_snapshot(snapshot);

	iter->pos = start;
	iter->eof = snapshot->eof;
	strbuf_init(&iter->refname_buf, 0);

	iter->base.oid = &iter->oid;

	iter->flags = flags;

	if (prefix && *prefix)
		/* Stop iteration after we've gone *past* prefix: */
		ref_iterator = prefix_ref_iterator_begin(ref_iterator, prefix, 0);

	return ref_iterator;
}