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
struct TYPE_2__ {int host_wr_err; int host_wr_timeout; int exec_wr_timeout; int npco_dma_malform; int host_nps_wr_err; } ;
union nps_core_int_ena_w1s {scalar_t__ value; TYPE_1__ s; } ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_CORE_INT_ENA_W1S ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void enable_nps_core_interrupts(struct nitrox_device *ndev)
{
	union nps_core_int_ena_w1s core_int;

	/* NPS core interrutps */
	core_int.value = 0;
	core_int.s.host_wr_err = 1;
	core_int.s.host_wr_timeout = 1;
	core_int.s.exec_wr_timeout = 1;
	core_int.s.npco_dma_malform = 1;
	core_int.s.host_nps_wr_err = 1;
	nitrox_write_csr(ndev, NPS_CORE_INT_ENA_W1S, core_int.value);
}