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
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ pcap_if_t ;

/* Variables and functions */
 TYPE_1__* acn_if_list ; 
 scalar_t__ if_sort (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sort_if_table(void) {
	pcap_if_t	*p1, *p2, *prev, *temp;
	int			has_swapped;

	if (!acn_if_list) return;				/* nothing to do if the list is empty */

	while (1) {
		p1 = acn_if_list;					/* start at the head of the list */
		prev = 0;
		has_swapped = 0;
		while ((p2 = p1->next)) {
			if (if_sort(p1->name, p2->name) > 0) {
				if (prev) {					/* we are swapping things that are _not_ at the head of the list */
					temp = p2->next;
					prev->next = p2;
					p2->next = p1;
					p1->next = temp;
				} else {					/* special treatment if we are swapping with the head of the list */
					temp = p2->next;
					acn_if_list= p2;
					p2->next = p1;
					p1->next = temp;
				}
				p1 = p2;
				prev = p1;
				has_swapped = 1;
			}
			prev = p1;
			p1 = p1->next;
		}
		if (has_swapped == 0)
			return;
	}
	return;
}