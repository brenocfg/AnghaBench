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
typedef  size_t u16 ;
struct ti_sci_resource {size_t sets; int /*<<< orphan*/  lock; TYPE_1__* desc; } ;
struct TYPE_2__ {size_t start; size_t num; int /*<<< orphan*/  res_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ti_sci_release_resource(struct ti_sci_resource *res, u16 id)
{
	unsigned long flags;
	u16 set;

	raw_spin_lock_irqsave(&res->lock, flags);
	for (set = 0; set < res->sets; set++) {
		if (res->desc[set].start <= id &&
		    (res->desc[set].num + res->desc[set].start) > id)
			clear_bit(id - res->desc[set].start,
				  res->desc[set].res_map);
	}
	raw_spin_unlock_irqrestore(&res->lock, flags);
}