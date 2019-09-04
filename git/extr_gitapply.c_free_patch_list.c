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
struct patch {struct patch* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_patch (struct patch*) ; 

__attribute__((used)) static void free_patch_list(struct patch *list)
{
	while (list) {
		struct patch *next = list->next;
		free_patch(list);
		list = next;
	}
}