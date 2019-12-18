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
struct TYPE_2__ {scalar_t__ offset; } ;
struct port_info {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 scalar_t__ A_XGM_XGM_INT_ENABLE ; 
 int /*<<< orphan*/  XGM_EXTRA_INTR_MASK ; 
 struct port_info* adap2pinfo (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void t3_xgm_intr_enable(adapter_t *adapter, int idx)
{
	struct port_info *pi = adap2pinfo(adapter, idx);

	t3_write_reg(adapter, A_XGM_XGM_INT_ENABLE + pi->mac.offset,
		     XGM_EXTRA_INTR_MASK);
}