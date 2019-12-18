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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct octeon_device {scalar_t__ chip; } ;
struct lio_cn23xx_pf {int /*<<< orphan*/  intr_enb_reg64; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_CN23XX_INTR_PKT_DATA ; 
 int OCTEON_ALL_INTR ; 
 int OCTEON_OUTPUT_INTR ; 
 int /*<<< orphan*/  lio_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lio_cn23xx_pf_disable_interrupt(struct octeon_device *oct, uint8_t intr_flag)
{
	struct lio_cn23xx_pf	*cn23xx = (struct lio_cn23xx_pf *)oct->chip;
	uint64_t		intr_val = 0;

	/* Disable Interrupts */
	if (intr_flag == OCTEON_ALL_INTR) {
		lio_write_csr64(oct, cn23xx->intr_enb_reg64, 0);
	} else if (intr_flag & OCTEON_OUTPUT_INTR) {
		intr_val = lio_read_csr64(oct, cn23xx->intr_enb_reg64);
		intr_val &= ~LIO_CN23XX_INTR_PKT_DATA;
		lio_write_csr64(oct, cn23xx->intr_enb_reg64, intr_val);
	}
}