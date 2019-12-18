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
struct lruhash_entry {struct lruhash_entry* overflow_next; } ;
struct lruhash_bin {struct lruhash_entry* overflow_list; } ;

/* Variables and functions */

void 
bin_overflow_remove(struct lruhash_bin* bin, struct lruhash_entry* entry)
{
	struct lruhash_entry* p = bin->overflow_list;
	struct lruhash_entry** prevp = &bin->overflow_list;
	while(p) {
		if(p == entry) {
			*prevp = p->overflow_next;
			return;
		}
		prevp = &p->overflow_next;
		p = p->overflow_next;
	}
}