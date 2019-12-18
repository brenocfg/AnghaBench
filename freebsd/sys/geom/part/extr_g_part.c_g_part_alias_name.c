#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum g_part_alias { ____Placeholder_g_part_alias } g_part_alias ;
struct TYPE_2__ {int alias; char const* lexeme; } ;

/* Variables and functions */
 int G_PART_ALIAS_COUNT ; 
 TYPE_1__* g_part_alias_list ; 

const char *
g_part_alias_name(enum g_part_alias alias)
{
	int i;

	for (i = 0; i < G_PART_ALIAS_COUNT; i++) {
		if (g_part_alias_list[i].alias != alias)
			continue;
		return (g_part_alias_list[i].lexeme);
	}

	return (NULL);
}