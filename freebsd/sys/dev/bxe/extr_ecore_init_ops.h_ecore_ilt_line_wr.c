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
typedef  scalar_t__ uint32_t ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  ILT_ADDR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILT_ADDR2 (int /*<<< orphan*/ ) ; 
 scalar_t__ PXP2_REG_RQ_ONCHIP_AT ; 
 scalar_t__ PXP2_REG_RQ_ONCHIP_AT_B0 ; 
 int /*<<< orphan*/  ecore_wr_64 (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_ilt_line_wr(struct bxe_softc *sc, int abs_idx,
			      ecore_dma_addr_t page_mapping)
{
	uint32_t reg;

	if (CHIP_IS_E1(sc))
		reg = PXP2_REG_RQ_ONCHIP_AT + abs_idx*8;
	else
		reg = PXP2_REG_RQ_ONCHIP_AT_B0 + abs_idx*8;

	ecore_wr_64(sc, reg, ILT_ADDR1(page_mapping), ILT_ADDR2(page_mapping));
}