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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct fman_rg {TYPE_2__* bmi_rg; TYPE_1__* dma_rg; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fmbm_spliodn; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fmdmplr; } ;

/* Variables and functions */
 int DMA_LIODN_SHIFT ; 
 int FM_LIODN_BASE_MASK ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

void fman_set_liodn_per_port(struct fman_rg *fman_rg, uint8_t port_id,
				uint16_t liodn_base,
				uint16_t liodn_ofst)
{
	uint32_t tmp;

	if ((port_id > 63) || (port_id < 1))
	        return;

	/* set LIODN base for this port */
	tmp = ioread32be(&fman_rg->dma_rg->fmdmplr[port_id / 2]);
	if (port_id % 2) {
		tmp &= ~FM_LIODN_BASE_MASK;
		tmp |= (uint32_t)liodn_base;
	} else {
		tmp &= ~(FM_LIODN_BASE_MASK << DMA_LIODN_SHIFT);
		tmp |= (uint32_t)liodn_base << DMA_LIODN_SHIFT;
	}
	iowrite32be(tmp, &fman_rg->dma_rg->fmdmplr[port_id / 2]);
	iowrite32be((uint32_t)liodn_ofst,
			&fman_rg->bmi_rg->fmbm_spliodn[port_id - 1]);
}