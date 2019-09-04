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
struct string_list_item {int /*<<< orphan*/  string; } ;
struct show_info {int width; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  string_list_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_remote_to_show_info(struct string_list_item *item, void *cb_data)
{
	struct show_info *info = cb_data;
	int n = strlen(item->string);
	if (n > info->width)
		info->width = n;
	string_list_insert(info->list, item->string);
	return 0;
}