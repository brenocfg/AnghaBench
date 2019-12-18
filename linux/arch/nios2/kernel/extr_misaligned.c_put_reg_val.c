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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int* reg_offsets ; 

__attribute__((used)) static inline void put_reg_val(struct pt_regs *fp, int reg, u32 val)
{
	u8 *p = ((u8 *)fp) + reg_offsets[reg];
	*(u32 *)p = val;
}