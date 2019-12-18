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
struct bgx {TYPE_1__* lmac; } ;
struct TYPE_2__ {int dmac; } ;

/* Variables and functions */
 scalar_t__ BGX_CMR_RX_DMACX_CAM ; 
 int MAX_DMAC_PER_LMAC ; 
 int /*<<< orphan*/  bgx_reg_write (struct bgx*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bgx_flush_dmac_addrs(struct bgx *bgx, int lmac)
{
	uint64_t offset;

	while (bgx->lmac[lmac].dmac > 0) {
		offset = ((bgx->lmac[lmac].dmac - 1) * sizeof(uint64_t)) +
		    (lmac * MAX_DMAC_PER_LMAC * sizeof(uint64_t));
		bgx_reg_write(bgx, 0, BGX_CMR_RX_DMACX_CAM + offset, 0);
		bgx->lmac[lmac].dmac--;
	}
}