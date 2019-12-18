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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ar2315_rst_reg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar2315_rst_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ar2315_rst_reg_mask(u32 reg, u32 mask, u32 val)
{
	u32 ret = ar2315_rst_reg_read(reg);

	ret &= ~mask;
	ret |= val;
	ar2315_rst_reg_write(reg, ret);
}