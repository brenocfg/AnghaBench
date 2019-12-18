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
typedef  int uint64_t ;
typedef  unsigned int uint32_t ;
struct TYPE_2__ {unsigned int pf_srn; } ;
struct octeon_device {unsigned int num_iqs; TYPE_1__ sriov_info; } ;

/* Variables and functions */
 int volatile BIT_ULL (unsigned int) ; 
 int volatile LIO_CN23XX_PKT_INPUT_CTL_RING_ENB ; 
 int volatile LIO_CN23XX_PKT_INPUT_CTL_RST ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_IQ_DOORBELL (unsigned int) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_IQ_PKT_CONTROL64 (unsigned int) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_PKTS_CREDIT (unsigned int) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_PKTS_SENT (unsigned int) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_PKT_IOQ_RING_RST ; 
 int lio_ms_to_ticks (int) ; 
 unsigned int lio_read_csr32 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 unsigned long long lio_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_sleep_timeout (int) ; 
 int /*<<< orphan*/  lio_write_csr32 (struct octeon_device*,int /*<<< orphan*/ ,unsigned int volatile) ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int volatile) ; 

__attribute__((used)) static void
lio_cn23xx_pf_disable_io_queues(struct octeon_device *oct)
{
	volatile uint64_t	d64;
	volatile uint32_t	d32;
	int			loop;
	unsigned int		q_no;
	uint32_t		ern, srn;

	srn = oct->sriov_info.pf_srn;
	ern = srn + oct->num_iqs;

	/* Disable Input Queues. */
	for (q_no = srn; q_no < ern; q_no++) {
		loop = lio_ms_to_ticks(1000);

		/* start the Reset for a particular ring */
		d64 = lio_read_csr64(oct,
				     LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
		d64 &= ~LIO_CN23XX_PKT_INPUT_CTL_RING_ENB;
		d64 |= LIO_CN23XX_PKT_INPUT_CTL_RST;
		lio_write_csr64(oct, LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
				d64);

		/*
		 * Wait until hardware indicates that the particular IQ
		 * is out of reset.
		 */
		d64 = lio_read_csr64(oct, LIO_CN23XX_SLI_PKT_IOQ_RING_RST);
		while (!(d64 & BIT_ULL(q_no)) && loop--) {
			d64 = lio_read_csr64(oct,
					     LIO_CN23XX_SLI_PKT_IOQ_RING_RST);
			lio_sleep_timeout(1);
			loop--;
		}

		/* Reset the doorbell register for this Input Queue. */
		lio_write_csr32(oct, LIO_CN23XX_SLI_IQ_DOORBELL(q_no),
				0xFFFFFFFF);
		while (((lio_read_csr64(oct,
					LIO_CN23XX_SLI_IQ_DOORBELL(q_no))) !=
			0ULL) && loop--) {
			lio_sleep_timeout(1);
		}
	}

	/* Disable Output Queues. */
	for (q_no = srn; q_no < ern; q_no++) {
		loop = lio_ms_to_ticks(1000);

		/*
		 * Wait until hardware indicates that the particular IQ
		 * is out of reset.It given that SLI_PKT_RING_RST is
		 * common for both IQs and OQs
		 */
		d64 = lio_read_csr64(oct, LIO_CN23XX_SLI_PKT_IOQ_RING_RST);
		while (!(d64 & BIT_ULL(q_no)) && loop--) {
			d64 = lio_read_csr64(oct,
					     LIO_CN23XX_SLI_PKT_IOQ_RING_RST);
			lio_sleep_timeout(1);
			loop--;
		}

		/* Reset the doorbell register for this Output Queue. */
		lio_write_csr32(oct, LIO_CN23XX_SLI_OQ_PKTS_CREDIT(q_no),
				0xFFFFFFFF);
		while ((lio_read_csr64(oct,
				       LIO_CN23XX_SLI_OQ_PKTS_CREDIT(q_no)) !=
			0ULL) && loop--) {
			lio_sleep_timeout(1);
		}

		/* clear the SLI_PKT(0..63)_CNTS[CNT] reg value */
		d32 = lio_read_csr32(oct, LIO_CN23XX_SLI_OQ_PKTS_SENT(q_no));
		lio_write_csr32(oct, LIO_CN23XX_SLI_OQ_PKTS_SENT(q_no),	d32);
	}
}