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
struct TYPE_4__ {int en; } ;
union cvmx_ciu3_iscx_w1c {scalar_t__ u64; TYPE_2__ s; } ;
struct TYPE_3__ {int intr; int intsn; } ;
union cvmx_ciu3_destx_pp_int {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
typedef  scalar_t__ u64 ;
struct octeon_ciu3_info {scalar_t__ ciu3_addr; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ CIU3_DEST_PP_INT (int) ; 
 scalar_t__ CIU3_ISC_W1C (int) ; 
 int CIU3_MBOX_PER_CORE ; 
 scalar_t__ OCTEON_IRQ_MBOX0 ; 
 struct octeon_ciu3_info* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int cvmx_get_local_core_num () ; 
 int /*<<< orphan*/  cvmx_read_csr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  octeon_ciu3_info ; 
 int octeon_irq_ciu3_base_mbox_intsn (int) ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

__attribute__((used)) static void octeon_irq_ciu3_mbox(void)
{
	union cvmx_ciu3_destx_pp_int dest_pp_int;
	struct octeon_ciu3_info *ciu3_info;
	u64 ciu3_addr;
	int core = cvmx_get_local_core_num();

	ciu3_info = __this_cpu_read(octeon_ciu3_info);
	ciu3_addr = ciu3_info->ciu3_addr;

	dest_pp_int.u64 = cvmx_read_csr(ciu3_addr + CIU3_DEST_PP_INT(1 + 3 * core));

	if (likely(dest_pp_int.s.intr)) {
		irq_hw_number_t intsn = dest_pp_int.s.intsn;
		int mbox = intsn - octeon_irq_ciu3_base_mbox_intsn(core);

		if (likely(mbox >= 0 && mbox < CIU3_MBOX_PER_CORE)) {
			do_IRQ(mbox + OCTEON_IRQ_MBOX0);
		} else {
			union cvmx_ciu3_iscx_w1c isc_w1c;
			u64 isc_w1c_addr = ciu3_addr + CIU3_ISC_W1C(intsn);

			isc_w1c.u64 = 0;
			isc_w1c.s.en = 1;
			cvmx_write_csr(isc_w1c_addr, isc_w1c.u64);
			cvmx_read_csr(isc_w1c_addr);
			spurious_interrupt();
		}
	} else {
		spurious_interrupt();
	}
}