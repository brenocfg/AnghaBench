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
struct merge_list {struct merge_list* next; } ;

/* Variables and functions */
 struct merge_list* merge_result ; 
 int /*<<< orphan*/  show_diff (struct merge_list*) ; 
 int /*<<< orphan*/  show_result_list (struct merge_list*) ; 

__attribute__((used)) static void show_result(void)
{
	struct merge_list *walk;

	walk = merge_result;
	while (walk) {
		show_result_list(walk);
		show_diff(walk);
		walk = walk->next;
	}
}