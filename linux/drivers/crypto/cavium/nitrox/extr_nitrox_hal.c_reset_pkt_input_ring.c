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
struct TYPE_2__ {scalar_t__ enb; } ;
union nps_pkt_in_instr_ctl {TYPE_1__ s; void* value; } ;
union nps_pkt_in_done_cnts {void* value; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int MAX_CSR_RETRIES ; 
 int /*<<< orphan*/  NPS_PKT_IN_DONE_CNTSX (int) ; 
 int /*<<< orphan*/  NPS_PKT_IN_INSTR_CTLX (int) ; 
 void* nitrox_read_csr (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void reset_pkt_input_ring(struct nitrox_device *ndev, int ring)
{
	union nps_pkt_in_instr_ctl pkt_in_ctl;
	union nps_pkt_in_done_cnts pkt_in_cnts;
	int max_retries = MAX_CSR_RETRIES;
	u64 offset;

	/* step 1: disable the ring, clear enable bit */
	offset = NPS_PKT_IN_INSTR_CTLX(ring);
	pkt_in_ctl.value = nitrox_read_csr(ndev, offset);
	pkt_in_ctl.s.enb = 0;
	nitrox_write_csr(ndev, offset, pkt_in_ctl.value);

	/* step 2: wait to clear [ENB] */
	usleep_range(100, 150);
	do {
		pkt_in_ctl.value = nitrox_read_csr(ndev, offset);
		if (!pkt_in_ctl.s.enb)
			break;
		udelay(50);
	} while (max_retries--);

	/* step 3: clear done counts */
	offset = NPS_PKT_IN_DONE_CNTSX(ring);
	pkt_in_cnts.value = nitrox_read_csr(ndev, offset);
	nitrox_write_csr(ndev, offset, pkt_in_cnts.value);
	usleep_range(50, 100);
}