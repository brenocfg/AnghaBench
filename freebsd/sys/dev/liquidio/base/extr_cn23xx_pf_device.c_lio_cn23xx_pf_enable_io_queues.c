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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int iq64B; int iq; int oq; } ;
struct TYPE_3__ {scalar_t__ pf_srn; } ;
struct octeon_device {scalar_t__ num_iqs; TYPE_2__ io_qmask; TYPE_1__ sriov_info; } ;

/* Variables and functions */
 int BIT_ULL (scalar_t__) ; 
 scalar_t__ BUSY_READING_REG_PF_LOOP_COUNT ; 
 int LIO_CN23XX_PKT_INPUT_CTL_IS_64B ; 
 int LIO_CN23XX_PKT_INPUT_CTL_QUIET ; 
 int LIO_CN23XX_PKT_INPUT_CTL_RING_ENB ; 
 int LIO_CN23XX_PKT_INPUT_CTL_RST ; 
 scalar_t__ LIO_CN23XX_PKT_OUTPUT_CTL_RING_ENB ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_IQ_PKT_CONTROL64 (scalar_t__) ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_OQ_PKT_CONTROL (scalar_t__) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,scalar_t__) ; 
 scalar_t__ lio_read_csr32 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int lio_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_csr32 (struct octeon_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lio_cn23xx_pf_enable_io_queues(struct octeon_device *oct)
{
	uint64_t	reg_val;
	uint32_t	ern, loop = BUSY_READING_REG_PF_LOOP_COUNT;
	uint32_t	q_no, srn;

	srn = oct->sriov_info.pf_srn;
	ern = srn + oct->num_iqs;

	for (q_no = srn; q_no < ern; q_no++) {
		/* set the corresponding IQ IS_64B bit */
		if (oct->io_qmask.iq64B & BIT_ULL(q_no - srn)) {
			reg_val = lio_read_csr64(oct,
					LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
			reg_val = reg_val | LIO_CN23XX_PKT_INPUT_CTL_IS_64B;
			lio_write_csr64(oct,
					LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
					reg_val);
		}
		/* set the corresponding IQ ENB bit */
		if (oct->io_qmask.iq & BIT_ULL(q_no - srn)) {
			/*
			 * IOQs are in reset by default in PEM2 mode,
			 * clearing reset bit
			 */
			reg_val = lio_read_csr64(oct,
					LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no));

			if (reg_val & LIO_CN23XX_PKT_INPUT_CTL_RST) {
				while ((reg_val &
					LIO_CN23XX_PKT_INPUT_CTL_RST) &&
				       !(reg_val &
					 LIO_CN23XX_PKT_INPUT_CTL_QUIET) &&
				       loop) {
					reg_val = lio_read_csr64(oct,
					LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
					loop--;
				}
				if (!loop) {
					lio_dev_err(oct, "clearing the reset reg failed or setting the quiet reg failed for qno: %u\n",
						    q_no);
					return (-1);
				}
				reg_val = reg_val &
					~LIO_CN23XX_PKT_INPUT_CTL_RST;
				lio_write_csr64(oct,
					LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
					reg_val);

				reg_val = lio_read_csr64(oct,
					LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
				if (reg_val & LIO_CN23XX_PKT_INPUT_CTL_RST) {
					lio_dev_err(oct, "clearing the reset failed for qno: %u\n",
						    q_no);
					return (-1);
				}
			}
			reg_val = lio_read_csr64(oct,
					LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no));
			reg_val = reg_val | LIO_CN23XX_PKT_INPUT_CTL_RING_ENB;
			lio_write_csr64(oct,
					LIO_CN23XX_SLI_IQ_PKT_CONTROL64(q_no),
					reg_val);
		}
	}
	for (q_no = srn; q_no < ern; q_no++) {
		uint32_t	reg_val;
		/* set the corresponding OQ ENB bit */
		if (oct->io_qmask.oq & BIT_ULL(q_no - srn)) {
			reg_val = lio_read_csr32(oct,
					LIO_CN23XX_SLI_OQ_PKT_CONTROL(q_no));
			reg_val = reg_val | LIO_CN23XX_PKT_OUTPUT_CTL_RING_ENB;
			lio_write_csr32(oct,
					LIO_CN23XX_SLI_OQ_PKT_CONTROL(q_no),
					reg_val);
		}
	}
	return (0);
}