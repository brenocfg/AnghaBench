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
struct string_list_item {scalar_t__ util; } ;
struct string_list {int dummy; } ;
struct oid_array {int dummy; } ;

/* Variables and functions */
 struct string_list_item* string_list_insert (struct string_list*,char const*) ; 
 scalar_t__ xcalloc (int,int) ; 

__attribute__((used)) static struct oid_array *submodule_commits(struct string_list *submodules,
					   const char *name)
{
	struct string_list_item *item;

	item = string_list_insert(submodules, name);
	if (item->util)
		return (struct oid_array *) item->util;

	/* NEEDSWORK: should we have oid_array_init()? */
	item->util = xcalloc(1, sizeof(struct oid_array));
	return (struct oid_array *) item->util;
}