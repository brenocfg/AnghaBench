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
 struct merge_list** merge_result_end ; 

__attribute__((used)) static void add_merge_entry(struct merge_list *entry)
{
	*merge_result_end = entry;
	merge_result_end = &entry->next;
}