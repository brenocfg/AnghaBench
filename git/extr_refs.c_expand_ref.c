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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int REF_ISBROKEN ; 
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_main_ref_store (struct repository*) ; 
 char** ref_rev_parse_rules ; 
 char* refs_resolve_ref_unsafe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*,int*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char const*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warn_ambiguous_refs ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* xstrdup (char const*) ; 

int expand_ref(struct repository *repo, const char *str, int len,
	       struct object_id *oid, char **ref)
{
	const char **p, *r;
	int refs_found = 0;
	struct strbuf fullref = STRBUF_INIT;

	*ref = NULL;
	for (p = ref_rev_parse_rules; *p; p++) {
		struct object_id oid_from_ref;
		struct object_id *this_result;
		int flag;

		this_result = refs_found ? &oid_from_ref : oid;
		strbuf_reset(&fullref);
		strbuf_addf(&fullref, *p, len, str);
		r = refs_resolve_ref_unsafe(get_main_ref_store(repo),
					    fullref.buf, RESOLVE_REF_READING,
					    this_result, &flag);
		if (r) {
			if (!refs_found++)
				*ref = xstrdup(r);
			if (!warn_ambiguous_refs)
				break;
		} else if ((flag & REF_ISSYMREF) && strcmp(fullref.buf, "HEAD")) {
			warning(_("ignoring dangling symref %s"), fullref.buf);
		} else if ((flag & REF_ISBROKEN) && strchr(fullref.buf, '/')) {
			warning(_("ignoring broken ref %s"), fullref.buf);
		}
	}
	strbuf_release(&fullref);
	return refs_found;
}