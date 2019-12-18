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
typedef  int uint32_t ;
struct fman_bmi_regs {int /*<<< orphan*/ * fmbm_arb; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_set_ports_bandwidth(struct fman_bmi_regs *bmi_rg, uint8_t *weights)
{
	int i;
	uint8_t shift;
	uint32_t tmp = 0;

	for (i = 0; i < 64; i++) {
		if (weights[i] > 1) { /* no need to write 1 since it is 0 */
			/* Add this port to tmp_reg */
			/* (each 8 ports result in one register)*/
			shift = (uint8_t)(32 - 4 * ((i % 8) + 1));
			tmp |= ((weights[i] - 1) << shift);
		}
		if (i % 8 == 7) { /* last in this set */
			iowrite32be(tmp, &bmi_rg->fmbm_arb[i / 8]);
			tmp = 0;
		}
	}
}