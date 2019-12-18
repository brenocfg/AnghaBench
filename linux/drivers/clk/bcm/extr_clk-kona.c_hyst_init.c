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
typedef  int u32 ;
struct ccu_data {int dummy; } ;
struct bcm_clk_hyst {int offset; int en_bit; int val_bit; } ;

/* Variables and functions */
 int __ccu_read (struct ccu_data*,int) ; 
 int /*<<< orphan*/  __ccu_write (struct ccu_data*,int,int) ; 
 int /*<<< orphan*/  hyst_exists (struct bcm_clk_hyst*) ; 

__attribute__((used)) static bool hyst_init(struct ccu_data *ccu, struct bcm_clk_hyst *hyst)
{
	u32 offset;
	u32 reg_val;
	u32 mask;

	if (!hyst_exists(hyst))
		return true;

	offset = hyst->offset;
	mask = (u32)1 << hyst->en_bit;
	mask |= (u32)1 << hyst->val_bit;

	reg_val = __ccu_read(ccu, offset);
	reg_val |= mask;
	__ccu_write(ccu, offset, reg_val);

	return true;
}