#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct string_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  keyword; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* keywords ; 
 int /*<<< orphan*/  list_config_item (struct string_list*,char const*,int /*<<< orphan*/ ) ; 

void list_config_color_sideband_slots(struct string_list *list, const char *prefix)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(keywords); i++)
		list_config_item(list, prefix, keywords[i].keyword);
}