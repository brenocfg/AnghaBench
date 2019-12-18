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
struct string_list_item {struct push_info* util; int /*<<< orphan*/  string; } ;
struct show_info {int width; int width2; int /*<<< orphan*/  list; } ;
struct push_info {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 struct string_list_item* string_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_push_to_show_info(struct string_list_item *push_item, void *cb_data)
{
	struct show_info *show_info = cb_data;
	struct push_info *push_info = push_item->util;
	struct string_list_item *item;
	int n;
	if ((n = strlen(push_item->string)) > show_info->width)
		show_info->width = n;
	if ((n = strlen(push_info->dest)) > show_info->width2)
		show_info->width2 = n;
	item = string_list_append(show_info->list, push_item->string);
	item->util = push_item->util;
	return 0;
}