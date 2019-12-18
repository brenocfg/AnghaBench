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
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_PIO_ADDR ; 
 int /*<<< orphan*/  A_TP_PIO_DATA ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void tp_wr_indirect(adapter_t *adap, unsigned int addr, u32 val)
{
	t3_write_reg(adap, A_TP_PIO_ADDR, addr);
	t3_write_reg(adap, A_TP_PIO_DATA, val);
}