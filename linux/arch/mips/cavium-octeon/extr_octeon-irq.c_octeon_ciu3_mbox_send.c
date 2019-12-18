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
struct TYPE_2__ {int raw; } ;
union cvmx_ciu3_iscx_w1s {scalar_t__ u64; TYPE_1__ s; } ;
typedef  scalar_t__ u64 ;
struct octeon_ciu3_info {scalar_t__ ciu3_addr; } ;

/* Variables and functions */
 scalar_t__ CIU3_ISC_W1S (unsigned int) ; 
 unsigned int CIU3_MBOX_PER_CORE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  octeon_ciu3_info ; 
 unsigned int octeon_irq_ciu3_mbox_intsn_for_cpu (int,unsigned int) ; 
 struct octeon_ciu3_info* per_cpu (int /*<<< orphan*/ ,int) ; 

void octeon_ciu3_mbox_send(int cpu, unsigned int mbox)
{
	struct octeon_ciu3_info *ciu3_info;
	unsigned int intsn;
	union cvmx_ciu3_iscx_w1s isc_w1s;
	u64 isc_w1s_addr;

	if (WARN_ON_ONCE(mbox >= CIU3_MBOX_PER_CORE))
		return;

	intsn = octeon_irq_ciu3_mbox_intsn_for_cpu(cpu, mbox);
	ciu3_info = per_cpu(octeon_ciu3_info, cpu);
	isc_w1s_addr = ciu3_info->ciu3_addr + CIU3_ISC_W1S(intsn);

	isc_w1s.u64 = 0;
	isc_w1s.s.raw = 1;

	cvmx_write_csr(isc_w1s_addr, isc_w1s.u64);
	cvmx_read_csr(isc_w1s_addr);
}