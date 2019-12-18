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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ pf_srn; scalar_t__ num_pf_rings; } ;
struct octeon_device {scalar_t__ pf_num; TYPE_1__ sriov_info; scalar_t__ chip; } ;
struct lio_cn23xx_pf {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 scalar_t__ LIO_CN23XX_PKT_OUTPUT_CTL_BMODE ; 
 scalar_t__ LIO_CN23XX_PKT_OUTPUT_CTL_DPTR ; 
 scalar_t__ LIO_CN23XX_PKT_OUTPUT_CTL_ES ; 
 scalar_t__ LIO_CN23XX_PKT_OUTPUT_CTL_ES_P ; 
 scalar_t__ LIO_CN23XX_PKT_OUTPUT_CTL_NSR ; 
 scalar_t__ LIO_CN23XX_PKT_OUTPUT_CTL_NSR_P ; 
 scalar_t__ LIO_CN23XX_PKT_OUTPUT_CTL_ROR ; 
 scalar_t__ LIO_CN23XX_PKT_OUTPUT_CTL_ROR_P ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_PKT_CONTROL (scalar_t__) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_PKT_INT_LEVELS (scalar_t__) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_WMARK ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OUT_BP_EN2_W1S ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OUT_BP_EN_W1S ; 
 scalar_t__ LIO_GET_IS_SLI_BP_ON_CFG (int /*<<< orphan*/ ) ; 
 int LIO_GET_OQ_INTR_PKT_CFG (int /*<<< orphan*/ ) ; 
 scalar_t__ LIO_GET_OQ_INTR_TIME_CFG (int /*<<< orphan*/ ) ; 
 int lio_cn23xx_pf_get_oq_ticks (struct octeon_device*,scalar_t__) ; 
 scalar_t__ lio_read_csr32 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_csr32 (struct octeon_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lio_cn23xx_pf_setup_global_output_regs(struct octeon_device *oct)
{
	struct lio_cn23xx_pf *cn23xx = (struct lio_cn23xx_pf *)oct->chip;
	uint64_t	time_threshold;
	uint32_t	ern, q_no, reg_val, srn;

	srn = oct->sriov_info.pf_srn;
	ern = srn + oct->sriov_info.num_pf_rings;

	if (LIO_GET_IS_SLI_BP_ON_CFG(cn23xx->conf)) {
		lio_write_csr64(oct, LIO_CN23XX_SLI_OQ_WMARK, 32);
	} else {
		/* Set Output queue watermark to 0 to disable backpressure */
		lio_write_csr64(oct, LIO_CN23XX_SLI_OQ_WMARK, 0);
	}

	for (q_no = srn; q_no < ern; q_no++) {
		reg_val = lio_read_csr32(oct,
					 LIO_CN23XX_SLI_OQ_PKT_CONTROL(q_no));

		/* set IPTR & DPTR */
		reg_val |= LIO_CN23XX_PKT_OUTPUT_CTL_DPTR;

		/* reset BMODE */
		reg_val &= ~(LIO_CN23XX_PKT_OUTPUT_CTL_BMODE);

		/*
		 * No Relaxed Ordering, No Snoop, 64-bit Byte swap for
		 * Output Queue ScatterList reset ROR_P, NSR_P
		 */
		reg_val &= ~(LIO_CN23XX_PKT_OUTPUT_CTL_ROR_P);
		reg_val &= ~(LIO_CN23XX_PKT_OUTPUT_CTL_NSR_P);

#if BYTE_ORDER == LITTLE_ENDIAN
		reg_val &= ~(LIO_CN23XX_PKT_OUTPUT_CTL_ES_P);
#else	/* BYTE_ORDER != LITTLE_ENDIAN  */
		reg_val |= (LIO_CN23XX_PKT_OUTPUT_CTL_ES_P);
#endif	/* BYTE_ORDER == LITTLE_ENDIAN */

		/*
		 * No Relaxed Ordering, No Snoop, 64-bit Byte swap for
		 * Output Queue Data reset ROR, NSR
		 */
		reg_val &= ~(LIO_CN23XX_PKT_OUTPUT_CTL_ROR);
		reg_val &= ~(LIO_CN23XX_PKT_OUTPUT_CTL_NSR);
		/* set the ES bit */
		reg_val |= (LIO_CN23XX_PKT_OUTPUT_CTL_ES);

		/* write all the selected settings */
		lio_write_csr32(oct, LIO_CN23XX_SLI_OQ_PKT_CONTROL(q_no),
				reg_val);

		/*
		 * Enabling these interrupt in oct->fn_list.enable_interrupt()
		 * routine which called after IOQ init.
		 * Set up interrupt packet and time thresholds
		 * for all the OQs
		 */
		time_threshold =lio_cn23xx_pf_get_oq_ticks(
		       oct, (uint32_t)LIO_GET_OQ_INTR_TIME_CFG(cn23xx->conf));

		lio_write_csr64(oct, LIO_CN23XX_SLI_OQ_PKT_INT_LEVELS(q_no),
				(LIO_GET_OQ_INTR_PKT_CFG(cn23xx->conf) |
				 (time_threshold << 32)));
	}

	/* Setting the water mark level for pko back pressure * */
	lio_write_csr64(oct, LIO_CN23XX_SLI_OQ_WMARK, 0x40);

	/* Enable channel-level backpressure */
	if (oct->pf_num)
		lio_write_csr64(oct, LIO_CN23XX_SLI_OUT_BP_EN2_W1S,
				0xffffffffffffffffULL);
	else
		lio_write_csr64(oct, LIO_CN23XX_SLI_OUT_BP_EN_W1S,
				0xffffffffffffffffULL);
}