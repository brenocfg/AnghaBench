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
struct TYPE_2__ {size_t num; size_t start; int /*<<< orphan*/  res_map; } ;

/* Variables and functions */
 size_t TI_SCI_RESOURCE_NULL ; 
 size_t find_first_zero_bit (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 

u16 ti_sci_get_free_resource(struct ti_sci_resource *res)
{
	unsigned long flags;
	u16 set, free_bit;

	raw_spin_lock_irqsave(&res->lock, flags);
	for (set = 0; set < res->sets; set++) {
		free_bit = find_first_zero_bit(res->desc[set].res_map,
					       res->desc[set].num);
		if (free_bit != res->desc[set].num) {
			set_bit(free_bit, res->desc[set].res_map);
			raw_spin_unlock_irqrestore(&res->lock, flags);
			return res->desc[set].start + free_bit;
		}
	}
	raw_spin_unlock_irqrestore(&res->lock, flags);

	return TI_SCI_RESOURCE_NULL;
}