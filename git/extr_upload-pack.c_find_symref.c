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
struct string_list_item {int /*<<< orphan*/  util; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 char* resolve_ref_unsafe (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 struct string_list_item* string_list_append (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_namespace (char const*) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_symref(const char *refname, const struct object_id *oid,
		       int flag, void *cb_data)
{
	const char *symref_target;
	struct string_list_item *item;

	if ((flag & REF_ISSYMREF) == 0)
		return 0;
	symref_target = resolve_ref_unsafe(refname, 0, NULL, &flag);
	if (!symref_target || (flag & REF_ISSYMREF) == 0)
		die("'%s' is a symref but it is not?", refname);
	item = string_list_append(cb_data, strip_namespace(refname));
	item->util = xstrdup(strip_namespace(symref_target));
	return 0;
}