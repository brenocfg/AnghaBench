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
struct edns_option {struct edns_option* next; } ;

/* Variables and functions */
 int edns_opt_compare (struct edns_option*,struct edns_option*) ; 

int edns_opt_list_compare(struct edns_option* p, struct edns_option* q)
{
	int r;
	while(p && q) {
		r = edns_opt_compare(p, q);
		if(r != 0)
			return r;
		p = p->next;
		q = q->next;
	}
	if(p || q) {
		/* uneven length lists */
		if(p) return 1;
		if(q) return -1;
	}
	return 0;
}