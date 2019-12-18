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
struct pt_section_list {struct pt_section_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_section_list_free (struct pt_section_list*) ; 

__attribute__((used)) static void pt_section_list_free_tail(struct pt_section_list *list)
{
	while (list) {
		struct pt_section_list *trash;

		trash = list;
		list = list->next;

		pt_section_list_free(trash);
	}
}