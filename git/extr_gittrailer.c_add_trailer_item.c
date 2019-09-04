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
struct trailer_item {char* token; char* value; int /*<<< orphan*/  list; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct trailer_item* xcalloc (int,int) ; 

__attribute__((used)) static struct trailer_item *add_trailer_item(struct list_head *head, char *tok,
					     char *val)
{
	struct trailer_item *new_item = xcalloc(sizeof(*new_item), 1);
	new_item->token = tok;
	new_item->value = val;
	list_add_tail(&new_item->list, head);
	return new_item;
}