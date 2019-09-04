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
struct object_id {int dummy; } ;
struct llist_item {int dummy; } ;
struct llist {int /*<<< orphan*/  back; } ;

/* Variables and functions */
 struct llist_item* llist_insert (struct llist*,int /*<<< orphan*/ ,struct object_id const*) ; 

__attribute__((used)) static inline struct llist_item *llist_insert_back(struct llist *list,
						   const struct object_id *oid)
{
	return llist_insert(list, list->back, oid);
}