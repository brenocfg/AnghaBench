#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; scalar_t__ len; } ;
struct object_id {int dummy; } ;
struct merge_remote_desc {TYPE_1__* obj; } ;
struct TYPE_4__ {struct object_id oid; } ;
struct commit {TYPE_2__ object; } ;
struct TYPE_3__ {scalar_t__ type; struct object_id oid; } ;

/* Variables and functions */
 scalar_t__ OBJ_TAG ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ dwim_ref (char const*,int,struct object_id*,char**) ; 
 struct commit* get_merge_parent (char const*) ; 
 scalar_t__ isdigit (char const) ; 
 struct merge_remote_desc* merge_remote_util (struct commit*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 scalar_t__ ref_exists (char*) ; 
 scalar_t__ starts_with (char*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_branchname (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,scalar_t__) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  type_name (scalar_t__) ; 

__attribute__((used)) static void merge_name(const char *remote, struct strbuf *msg)
{
	struct commit *remote_head;
	struct object_id branch_head;
	struct strbuf buf = STRBUF_INIT;
	struct strbuf bname = STRBUF_INIT;
	struct merge_remote_desc *desc;
	const char *ptr;
	char *found_ref;
	int len, early;

	strbuf_branchname(&bname, remote, 0);
	remote = bname.buf;

	oidclr(&branch_head);
	remote_head = get_merge_parent(remote);
	if (!remote_head)
		die(_("'%s' does not point to a commit"), remote);

	if (dwim_ref(remote, strlen(remote), &branch_head, &found_ref) > 0) {
		if (starts_with(found_ref, "refs/heads/")) {
			strbuf_addf(msg, "%s\t\tbranch '%s' of .\n",
				    oid_to_hex(&branch_head), remote);
			goto cleanup;
		}
		if (starts_with(found_ref, "refs/tags/")) {
			strbuf_addf(msg, "%s\t\ttag '%s' of .\n",
				    oid_to_hex(&branch_head), remote);
			goto cleanup;
		}
		if (starts_with(found_ref, "refs/remotes/")) {
			strbuf_addf(msg, "%s\t\tremote-tracking branch '%s' of .\n",
				    oid_to_hex(&branch_head), remote);
			goto cleanup;
		}
	}

	/* See if remote matches <name>^^^.. or <name>~<number> */
	for (len = 0, ptr = remote + strlen(remote);
	     remote < ptr && ptr[-1] == '^';
	     ptr--)
		len++;
	if (len)
		early = 1;
	else {
		early = 0;
		ptr = strrchr(remote, '~');
		if (ptr) {
			int seen_nonzero = 0;

			len++; /* count ~ */
			while (*++ptr && isdigit(*ptr)) {
				seen_nonzero |= (*ptr != '0');
				len++;
			}
			if (*ptr)
				len = 0; /* not ...~<number> */
			else if (seen_nonzero)
				early = 1;
			else if (len == 1)
				early = 1; /* "name~" is "name~1"! */
		}
	}
	if (len) {
		struct strbuf truname = STRBUF_INIT;
		strbuf_addf(&truname, "refs/heads/%s", remote);
		strbuf_setlen(&truname, truname.len - len);
		if (ref_exists(truname.buf)) {
			strbuf_addf(msg,
				    "%s\t\tbranch '%s'%s of .\n",
				    oid_to_hex(&remote_head->object.oid),
				    truname.buf + 11,
				    (early ? " (early part)" : ""));
			strbuf_release(&truname);
			goto cleanup;
		}
		strbuf_release(&truname);
	}

	desc = merge_remote_util(remote_head);
	if (desc && desc->obj && desc->obj->type == OBJ_TAG) {
		strbuf_addf(msg, "%s\t\t%s '%s'\n",
			    oid_to_hex(&desc->obj->oid),
			    type_name(desc->obj->type),
			    remote);
		goto cleanup;
	}

	strbuf_addf(msg, "%s\t\tcommit '%s'\n",
		oid_to_hex(&remote_head->object.oid), remote);
cleanup:
	strbuf_release(&buf);
	strbuf_release(&bname);
}