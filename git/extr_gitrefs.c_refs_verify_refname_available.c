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
struct string_list {int dummy; } ;
struct strbuf {int len; char const* buf; } ;
struct ref_store {int dummy; } ;
struct ref_iterator {char const* refname; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  DO_FOR_EACH_INCLUDE_BROKEN ; 
 int ITER_DONE ; 
 int ITER_OK ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (struct strbuf*) ; 
 char* find_descendant_ref (char const*,struct string_list const*,struct string_list const*) ; 
 int /*<<< orphan*/  ref_iterator_abort (struct ref_iterator*) ; 
 int ref_iterator_advance (struct ref_iterator*) ; 
 int /*<<< orphan*/  refs_read_raw_ref (struct ref_store*,char const*,struct object_id*,struct strbuf*,unsigned int*) ; 
 struct ref_iterator* refs_ref_iterator_begin (struct ref_store*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ string_list_has_string (struct string_list const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int refs_verify_refname_available(struct ref_store *refs,
				  const char *refname,
				  const struct string_list *extras,
				  const struct string_list *skip,
				  struct strbuf *err)
{
	const char *slash;
	const char *extra_refname;
	struct strbuf dirname = STRBUF_INIT;
	struct strbuf referent = STRBUF_INIT;
	struct object_id oid;
	unsigned int type;
	struct ref_iterator *iter;
	int ok;
	int ret = -1;

	/*
	 * For the sake of comments in this function, suppose that
	 * refname is "refs/foo/bar".
	 */

	assert(err);

	strbuf_grow(&dirname, strlen(refname) + 1);
	for (slash = strchr(refname, '/'); slash; slash = strchr(slash + 1, '/')) {
		/* Expand dirname to the new prefix, not including the trailing slash: */
		strbuf_add(&dirname, refname + dirname.len, slash - refname - dirname.len);

		/*
		 * We are still at a leading dir of the refname (e.g.,
		 * "refs/foo"; if there is a reference with that name,
		 * it is a conflict, *unless* it is in skip.
		 */
		if (skip && string_list_has_string(skip, dirname.buf))
			continue;

		if (!refs_read_raw_ref(refs, dirname.buf, &oid, &referent, &type)) {
			strbuf_addf(err, _("'%s' exists; cannot create '%s'"),
				    dirname.buf, refname);
			goto cleanup;
		}

		if (extras && string_list_has_string(extras, dirname.buf)) {
			strbuf_addf(err, _("cannot process '%s' and '%s' at the same time"),
				    refname, dirname.buf);
			goto cleanup;
		}
	}

	/*
	 * We are at the leaf of our refname (e.g., "refs/foo/bar").
	 * There is no point in searching for a reference with that
	 * name, because a refname isn't considered to conflict with
	 * itself. But we still need to check for references whose
	 * names are in the "refs/foo/bar/" namespace, because they
	 * *do* conflict.
	 */
	strbuf_addstr(&dirname, refname + dirname.len);
	strbuf_addch(&dirname, '/');

	iter = refs_ref_iterator_begin(refs, dirname.buf, 0,
				       DO_FOR_EACH_INCLUDE_BROKEN);
	while ((ok = ref_iterator_advance(iter)) == ITER_OK) {
		if (skip &&
		    string_list_has_string(skip, iter->refname))
			continue;

		strbuf_addf(err, _("'%s' exists; cannot create '%s'"),
			    iter->refname, refname);
		ref_iterator_abort(iter);
		goto cleanup;
	}

	if (ok != ITER_DONE)
		BUG("error while iterating over references");

	extra_refname = find_descendant_ref(dirname.buf, extras, skip);
	if (extra_refname)
		strbuf_addf(err, _("cannot process '%s' and '%s' at the same time"),
			    refname, extra_refname);
	else
		ret = 0;

cleanup:
	strbuf_release(&referent);
	strbuf_release(&dirname);
	return ret;
}