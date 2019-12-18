#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ccu_data {int dummy; } ;
struct bcm_clk_trig {int dummy; } ;
struct bcm_clk_gate {int dummy; } ;
struct TYPE_4__ {scalar_t__ scaled_div; } ;
struct TYPE_3__ {TYPE_2__ s; } ;
struct bcm_clk_div {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ccu_write_disable (struct ccu_data*) ; 
 int /*<<< orphan*/  __ccu_write_enable (struct ccu_data*) ; 
 int __div_commit (struct ccu_data*,struct bcm_clk_gate*,struct bcm_clk_div*,struct bcm_clk_trig*) ; 
 unsigned long ccu_lock (struct ccu_data*) ; 
 int /*<<< orphan*/  ccu_unlock (struct ccu_data*,unsigned long) ; 
 int /*<<< orphan*/  divider_is_fixed (struct bcm_clk_div*) ; 

__attribute__((used)) static int divider_write(struct ccu_data *ccu, struct bcm_clk_gate *gate,
			struct bcm_clk_div *div, struct bcm_clk_trig *trig,
			u64 scaled_div)
{
	unsigned long flags;
	u64 previous;
	int ret;

	BUG_ON(divider_is_fixed(div));

	previous = div->u.s.scaled_div;
	if (previous == scaled_div)
		return 0;	/* No change */

	div->u.s.scaled_div = scaled_div;

	flags = ccu_lock(ccu);
	__ccu_write_enable(ccu);

	ret = __div_commit(ccu, gate, div, trig);

	__ccu_write_disable(ccu);
	ccu_unlock(ccu, flags);

	if (ret)
		div->u.s.scaled_div = previous;		/* Revert the change */

	return ret;

}