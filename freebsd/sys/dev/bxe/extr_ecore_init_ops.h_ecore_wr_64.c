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
 int /*<<< orphan*/  REG_WR_DMAE_LEN (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ecore_wr_64(struct bxe_softc *sc, uint32_t reg, uint32_t val_lo,
			uint32_t val_hi)
{
	uint32_t wb_write[2];

	wb_write[0] = val_lo;
	wb_write[1] = val_hi;
	REG_WR_DMAE_LEN(sc, reg, wb_write, 2);
}