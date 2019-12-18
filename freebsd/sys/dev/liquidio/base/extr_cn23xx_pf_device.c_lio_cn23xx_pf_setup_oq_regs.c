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
typedef  size_t uint32_t ;
struct TYPE_2__ {scalar_t__ pf_srn; } ;
struct octeon_device {int /*<<< orphan*/  msix_on; TYPE_1__ sriov_info; scalar_t__ chip; struct lio_droq** droq; } ;
struct lio_droq {int desc_ring_dma; size_t max_count; size_t buffer_size; int /*<<< orphan*/  pkts_credit_reg; int /*<<< orphan*/  pkts_sent_reg; } ;
struct lio_cn23xx_pf {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 size_t LIO_CN23XX_PKT_OUTPUT_CTL_CENB ; 
 size_t LIO_CN23XX_PKT_OUTPUT_CTL_TENB ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_BASE_ADDR64 (size_t) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_BUFF_INFO_SIZE (size_t) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_PKTS_CREDIT (size_t) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_PKTS_SENT (size_t) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_PKT_CONTROL (size_t) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_PKT_INT_LEVELS (size_t) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_SIZE (size_t) ; 
 scalar_t__ LIO_GET_OQ_INTR_PKT_CFG (int /*<<< orphan*/ ) ; 
 scalar_t__ LIO_GET_OQ_INTR_TIME_CFG (int /*<<< orphan*/ ) ; 
 int lio_cn23xx_pf_get_oq_ticks (struct octeon_device*,size_t) ; 
 size_t lio_read_csr32 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_csr32 (struct octeon_device*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lio_cn23xx_pf_setup_oq_regs(struct octeon_device *oct, uint32_t oq_no)
{
	struct lio_droq		*droq = oct->droq[oq_no];
	struct lio_cn23xx_pf	*cn23xx = (struct lio_cn23xx_pf *)oct->chip;
	uint64_t		cnt_threshold;
	uint64_t		time_threshold;
	uint32_t		reg_val;

	oq_no += oct->sriov_info.pf_srn;

	lio_write_csr64(oct, LIO_CN23XX_SLI_OQ_BASE_ADDR64(oq_no),
			droq->desc_ring_dma);
	lio_write_csr32(oct, LIO_CN23XX_SLI_OQ_SIZE(oq_no), droq->max_count);

	lio_write_csr32(oct, LIO_CN23XX_SLI_OQ_BUFF_INFO_SIZE(oq_no),
			droq->buffer_size);

	/* pkt_sent and pkts_credit regs */
	droq->pkts_sent_reg = LIO_CN23XX_SLI_OQ_PKTS_SENT(oq_no);
	droq->pkts_credit_reg = LIO_CN23XX_SLI_OQ_PKTS_CREDIT(oq_no);

	if (!oct->msix_on) {
		/*
		 * Enable this output queue to generate Packet Timer
		 * Interrupt
		 */
		reg_val =
		    lio_read_csr32(oct, LIO_CN23XX_SLI_OQ_PKT_CONTROL(oq_no));
		reg_val |= LIO_CN23XX_PKT_OUTPUT_CTL_TENB;
		lio_write_csr32(oct, LIO_CN23XX_SLI_OQ_PKT_CONTROL(oq_no),
				reg_val);

		/*
		 * Enable this output queue to generate Packet Count
		 * Interrupt
		 */
		reg_val =
		    lio_read_csr32(oct, LIO_CN23XX_SLI_OQ_PKT_CONTROL(oq_no));
		reg_val |= LIO_CN23XX_PKT_OUTPUT_CTL_CENB;
		lio_write_csr32(oct, LIO_CN23XX_SLI_OQ_PKT_CONTROL(oq_no),
				reg_val);
	} else {
		time_threshold = lio_cn23xx_pf_get_oq_ticks(oct,
			(uint32_t)LIO_GET_OQ_INTR_TIME_CFG(cn23xx->conf));
		cnt_threshold = (uint32_t)LIO_GET_OQ_INTR_PKT_CFG(cn23xx->conf);

		lio_write_csr64(oct, LIO_CN23XX_SLI_OQ_PKT_INT_LEVELS(oq_no),
				((time_threshold << 32 | cnt_threshold)));
	}
}