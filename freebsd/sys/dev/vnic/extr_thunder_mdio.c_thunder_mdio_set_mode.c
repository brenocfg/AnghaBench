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
typedef  int /*<<< orphan*/  uint64_t ;
struct thunder_mdio_softc {int mode; } ;
typedef  enum thunder_mdio_mode { ____Placeholder_thunder_mdio_mode } thunder_mdio_mode ;

/* Variables and functions */
 int MODE_IEEE_C22 ; 
 int /*<<< orphan*/  SMI_CLK ; 
 int /*<<< orphan*/  SMI_CLK_MODE ; 
 int /*<<< orphan*/  SMI_CLK_PREAMBLE ; 
 int /*<<< orphan*/  mdio_reg_read (struct thunder_mdio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_reg_write (struct thunder_mdio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
thunder_mdio_set_mode(struct thunder_mdio_softc *sc,
    enum thunder_mdio_mode mode)
{
	uint64_t smi_clk;

	if (sc->mode == mode)
		return;

	/* Set mode, IEEE CLAUSE 22 or IEEE CAUSE 45 */
	smi_clk = mdio_reg_read(sc, SMI_CLK);
	if (mode == MODE_IEEE_C22)
		smi_clk &= ~SMI_CLK_MODE;
	else
		smi_clk |= SMI_CLK_MODE;
	/* Enable sending 32 bit preable on SMI transactions */
	smi_clk |= SMI_CLK_PREAMBLE;
	/* Saved setings */
	mdio_reg_write(sc, SMI_CLK, smi_clk);
	sc->mode = mode;
}