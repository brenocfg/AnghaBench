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
 int /*<<< orphan*/  string_list_insert (struct string_list*,char const*) ; 

__attribute__((used)) static int add_existing(const char *refname, const struct object_id *oid,
			int flag, void *cbdata)
{
	struct string_list *list = (struct string_list *)cbdata;
	string_list_insert(list, refname);
	return 0;
}