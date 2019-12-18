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
struct val_neg_zone {int in_use; int /*<<< orphan*/  count; struct val_neg_zone* parent; } ;

/* Variables and functions */

void val_neg_zone_take_inuse(struct val_neg_zone* zone)
{
	if(!zone->in_use) {
		struct val_neg_zone* p;
		zone->in_use = 1;
		/* increase usage count of all parents */
		for(p=zone; p; p = p->parent) {
			p->count++;
		}
	}
}