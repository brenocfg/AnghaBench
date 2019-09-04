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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct ref_store {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refs_verify_refname_available (struct ref_store*,char const*,int /*<<< orphan*/ *,struct string_list*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_insert (struct string_list*,char const*) ; 

int refs_rename_ref_available(struct ref_store *refs,
			      const char *old_refname,
			      const char *new_refname)
{
	struct string_list skip = STRING_LIST_INIT_NODUP;
	struct strbuf err = STRBUF_INIT;
	int ok;

	string_list_insert(&skip, old_refname);
	ok = !refs_verify_refname_available(refs, new_refname,
					    NULL, &skip, &err);
	if (!ok)
		error("%s", err.buf);

	string_list_clear(&skip, 0);
	strbuf_release(&err);
	return ok;
}