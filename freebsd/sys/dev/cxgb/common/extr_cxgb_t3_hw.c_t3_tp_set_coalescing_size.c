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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_PARA_REG2 ; 
 int /*<<< orphan*/  A_TP_PARA_REG3 ; 
 int EINVAL ; 
 int F_RXCOALESCEENABLE ; 
 int F_RXCOALESCEPSHEN ; 
 unsigned int MAX_RX_COALESCING_LEN ; 
 int V_MAXRXDATA (unsigned int) ; 
 int V_RXCOALESCESIZE (unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int t3_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int t3_tp_set_coalescing_size(adapter_t *adap, unsigned int size, int psh)
{
	u32 val;

	if (size > MAX_RX_COALESCING_LEN)
		return -EINVAL;

	val = t3_read_reg(adap, A_TP_PARA_REG3);
	val &= ~(F_RXCOALESCEENABLE | F_RXCOALESCEPSHEN);

	if (size) {
		val |= F_RXCOALESCEENABLE;
		if (psh)
			val |= F_RXCOALESCEPSHEN;
		size = min(MAX_RX_COALESCING_LEN, size);
		t3_write_reg(adap, A_TP_PARA_REG2, V_RXCOALESCESIZE(size) |
			     V_MAXRXDATA(MAX_RX_COALESCING_LEN));
	}
	t3_write_reg(adap, A_TP_PARA_REG3, val);
	return 0;
}