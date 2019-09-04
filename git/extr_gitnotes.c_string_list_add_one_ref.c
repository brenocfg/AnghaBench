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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*) ; 
 int /*<<< orphan*/  unsorted_string_list_has_string (struct string_list*,char const*) ; 

__attribute__((used)) static int string_list_add_one_ref(const char *refname, const struct object_id *oid,
				   int flag, void *cb)
{
	struct string_list *refs = cb;
	if (!unsorted_string_list_has_string(refs, refname))
		string_list_append(refs, refname);
	return 0;
}