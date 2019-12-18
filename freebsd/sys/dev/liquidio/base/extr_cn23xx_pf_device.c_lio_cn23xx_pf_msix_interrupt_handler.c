#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
struct octeon_device {int /*<<< orphan*/  pf_num; struct lio_droq** droq; } ;
struct lio_ioq_vector {size_t droq_index; int /*<<< orphan*/  ioq_num; struct octeon_device* oct_dev; } ;
struct lio_droq {int /*<<< orphan*/  pkts_sent_reg; } ;

/* Variables and functions */
 int LIO_CN23XX_INTR_PI_INT ; 
 int LIO_CN23XX_INTR_PO_INT ; 
 int LIO_MSIX_PI_INT ; 
 int LIO_MSIX_PO_INT ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lio_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
lio_cn23xx_pf_msix_interrupt_handler(void *dev)
{
	struct lio_ioq_vector	*ioq_vector = (struct lio_ioq_vector *)dev;
	struct octeon_device	*oct = ioq_vector->oct_dev;
	struct lio_droq		*droq = oct->droq[ioq_vector->droq_index];
	uint64_t		pkts_sent;
	uint64_t		ret = 0;

	if (droq == NULL) {
		lio_dev_err(oct, "23XX bringup FIXME: oct pfnum:%d ioq_vector->ioq_num :%d droq is NULL\n",
			    oct->pf_num, ioq_vector->ioq_num);
		return (0);
	}
	pkts_sent = lio_read_csr64(oct, droq->pkts_sent_reg);

	/*
	 * If our device has interrupted, then proceed. Also check
	 * for all f's if interrupt was triggered on an error
	 * and the PCI read fails.
	 */
	if (!pkts_sent || (pkts_sent == 0xFFFFFFFFFFFFFFFFULL))
		return (ret);

	/* Write count reg in sli_pkt_cnts to clear these int. */
	if (pkts_sent & LIO_CN23XX_INTR_PO_INT)
		ret |= LIO_MSIX_PO_INT;

	if (pkts_sent & LIO_CN23XX_INTR_PI_INT)
		/* We will clear the count when we update the read_index. */
		ret |= LIO_MSIX_PI_INT;

	/*
	 * Never need to handle msix mbox intr for pf. They arrive on the last
	 * msix
	 */
	return (ret);
}