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
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ GIT_SHA1_HEXSZ ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  lookup_commit_reference (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_splice (struct strbuf*,int,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int replace_parents(struct strbuf *buf, int argc, const char **argv)
{
	struct strbuf new_parents = STRBUF_INIT;
	const char *parent_start, *parent_end;
	int i;

	/* find existing parents */
	parent_start = buf->buf;
	parent_start += GIT_SHA1_HEXSZ + 6; /* "tree " + "hex sha1" + "\n" */
	parent_end = parent_start;

	while (starts_with(parent_end, "parent "))
		parent_end += 48; /* "parent " + "hex sha1" + "\n" */

	/* prepare new parents */
	for (i = 0; i < argc; i++) {
		struct object_id oid;
		if (get_oid(argv[i], &oid) < 0) {
			strbuf_release(&new_parents);
			return error(_("not a valid object name: '%s'"),
				     argv[i]);
		}
		if (!lookup_commit_reference(the_repository, &oid)) {
			strbuf_release(&new_parents);
			return error(_("could not parse %s"), argv[i]);
		}
		strbuf_addf(&new_parents, "parent %s\n", oid_to_hex(&oid));
	}

	/* replace existing parents with new ones */
	strbuf_splice(buf, parent_start - buf->buf, parent_end - parent_start,
		      new_parents.buf, new_parents.len);

	strbuf_release(&new_parents);
	return 0;
}