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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ccu_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  width; int /*<<< orphan*/  shift; int /*<<< orphan*/  offset; } ;
struct TYPE_3__ {TYPE_2__ s; int /*<<< orphan*/  fixed; } ;
struct bcm_clk_div {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ccu_read (struct ccu_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitfield_extract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long ccu_lock (struct ccu_data*) ; 
 int /*<<< orphan*/  ccu_unlock (struct ccu_data*,unsigned long) ; 
 scalar_t__ divider_is_fixed (struct bcm_clk_div*) ; 
 int /*<<< orphan*/  scaled_div_value (struct bcm_clk_div*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 divider_read_scaled(struct ccu_data *ccu, struct bcm_clk_div *div)
{
	unsigned long flags;
	u32 reg_val;
	u32 reg_div;

	if (divider_is_fixed(div))
		return (u64)div->u.fixed;

	flags = ccu_lock(ccu);
	reg_val = __ccu_read(ccu, div->u.s.offset);
	ccu_unlock(ccu, flags);

	/* Extract the full divider field from the register value */
	reg_div = bitfield_extract(reg_val, div->u.s.shift, div->u.s.width);

	/* Return the scaled divisor value it represents */
	return scaled_div_value(div, reg_div);
}