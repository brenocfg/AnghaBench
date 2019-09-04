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
struct string_list_item {int /*<<< orphan*/ * util; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct rename_info {int /*<<< orphan*/  remote_branches; int /*<<< orphan*/  old_name; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 struct strbuf STRBUF_INIT ; 
 char* resolve_ref_unsafe (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ starts_with (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 struct string_list_item* string_list_append (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * xstrdup (char const*) ; 

__attribute__((used)) static int read_remote_branches(const char *refname,
	const struct object_id *oid, int flags, void *cb_data)
{
	struct rename_info *rename = cb_data;
	struct strbuf buf = STRBUF_INIT;
	struct string_list_item *item;
	int flag;
	const char *symref;

	strbuf_addf(&buf, "refs/remotes/%s/", rename->old_name);
	if (starts_with(refname, buf.buf)) {
		item = string_list_append(rename->remote_branches, refname);
		symref = resolve_ref_unsafe(refname, RESOLVE_REF_READING,
					    NULL, &flag);
		if (symref && (flag & REF_ISSYMREF))
			item->util = xstrdup(symref);
		else
			item->util = NULL;
	}
	strbuf_release(&buf);

	return 0;
}