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
typedef  int /*<<< orphan*/  uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 scalar_t__ DMAE_READY (struct bxe_softc*) ; 
 int /*<<< orphan*/  VIRT_WR_DMAE_LEN (struct bxe_softc*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_ind_wr (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_str_wr (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_init_wr_wb(struct bxe_softc *sc, uint32_t addr,
			     const uint32_t *data, uint32_t len)
{
	if (DMAE_READY(sc))
		VIRT_WR_DMAE_LEN(sc, data, addr, len, 0);

	/* in E1 chips BIOS initiated ZLR may interrupt widebus writes */
	else if (CHIP_IS_E1(sc))
		ecore_init_ind_wr(sc, addr, data, len);

	/* in later chips PXP root complex handles BIOS ZLR w/o interrupting */
	else
		ecore_init_str_wr(sc, addr, data, len);
}