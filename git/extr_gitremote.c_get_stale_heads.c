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
struct stale_heads_info {struct refspec* rs; struct ref** stale_refs_tail; struct string_list* ref_names; } ;
struct refspec {int dummy; } ;
struct ref {int /*<<< orphan*/  name; struct ref* next; } ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,struct stale_heads_info*) ; 
 int /*<<< orphan*/  get_stale_heads_cb ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 

struct ref *get_stale_heads(struct refspec *rs, struct ref *fetch_map)
{
	struct ref *ref, *stale_refs = NULL;
	struct string_list ref_names = STRING_LIST_INIT_NODUP;
	struct stale_heads_info info;

	info.ref_names = &ref_names;
	info.stale_refs_tail = &stale_refs;
	info.rs = rs;
	for (ref = fetch_map; ref; ref = ref->next)
		string_list_append(&ref_names, ref->name);
	string_list_sort(&ref_names);
	for_each_ref(get_stale_heads_cb, &info);
	string_list_clear(&ref_names, 0);
	return stale_refs;
}