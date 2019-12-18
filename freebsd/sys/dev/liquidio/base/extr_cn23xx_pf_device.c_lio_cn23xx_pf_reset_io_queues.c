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
typedef  int volatile uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ pf_srn; scalar_t__ num_pf_rings; } ;
struct octeon_device {TYPE_1__ sriov_info; } ;

/* Variables and functions */
 scalar_t__ BUSY_READING_REG_PF_LOOP_COUNT ; 
 int volatile LIO_CN23XX_PKT_INPUT_CTL_QUIET ; 
 int volatile LIO_CN23XX_PKT_INPUT_CTL_RST ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_IQ_PKT_CONTROL64 (scalar_t__) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,scalar_t__) ; 
 int lio_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int volatile) ; 

__attribute__((used)) static int
lio_cn23xx_pf_reset_io_queues(struct octeon_device *oct)
{
	uint64_t	d64;
	uint32_t	ern, loop = BUSY_READING_REG_PF_LOOP_COUNT;
	uint32_t	q_no, srn;
	int		ret_val = 0;

	srn = oct->sriov_info.pf_srn;
	ern = srn + oct->sriov_info.num_pf_rings;

	/* As per HRM reg description, s/w cant write 0 to ENB. */
	/* to make the queue off, need to set the RST bit. */

	/* Reset the Enable bit for all the 64 IQs.  */
	for (q_no = srn; q_no < ern; q_no++) {
		/* set RST bit to 1. This bit applies to both IQ and OQ */
		d64 = lio_read_csr64(oct,
				     LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
		d64 = d64 | LIO_CN23XX_PKT_INPUT_CTL_RST;
		lio_write_csr64(oct,
				LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no), d64);
	}

	/* wait until the RST bit is clear or the RST and quiet bits are set */
	for (q_no = srn; q_no < ern; q_no++) {
		volatile uint64_t reg_val =
			lio_read_csr64(oct,
				       LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
		while ((reg_val & LIO_CN23XX_PKT_INPUT_CTL_RST) &&
		       !(reg_val & LIO_CN23XX_PKT_INPUT_CTL_QUIET) &&
		       loop) {
			reg_val = lio_read_csr64(oct,
				       LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
			loop--;
		}

		if (!loop) {
			lio_dev_err(oct,
				    "clearing the reset reg failed or setting the quiet reg failed for qno: %u\n",
				    q_no);
			return (-1);
		}

		reg_val &= ~LIO_CN23XX_PKT_INPUT_CTL_RST;
		lio_write_csr64(oct, LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
				reg_val);

		reg_val = lio_read_csr64(oct,
					 LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
		if (reg_val & LIO_CN23XX_PKT_INPUT_CTL_RST) {
			lio_dev_err(oct, "clearing the reset failed for qno: %u\n",
				    q_no);
			ret_val = -1;
		}
	}

	return (ret_val);
}