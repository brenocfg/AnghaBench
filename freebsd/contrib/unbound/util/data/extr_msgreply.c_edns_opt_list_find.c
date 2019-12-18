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
typedef  scalar_t__ uint16_t ;
struct edns_option {scalar_t__ opt_code; struct edns_option* next; } ;

/* Variables and functions */

struct edns_option* edns_opt_list_find(struct edns_option* list, uint16_t code)
{
	struct edns_option* p;
	for(p=list; p; p=p->next) {
		if(p->opt_code == code)
			return p;
	}
	return NULL;
}