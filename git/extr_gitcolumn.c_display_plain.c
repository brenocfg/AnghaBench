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
struct string_list {int nr; TYPE_1__* items; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,char*,char const*) ; 

__attribute__((used)) static void display_plain(const struct string_list *list,
			  const char *indent, const char *nl)
{
	int i;

	for (i = 0; i < list->nr; i++)
		printf("%s%s%s", indent, list->items[i].string, nl);
}