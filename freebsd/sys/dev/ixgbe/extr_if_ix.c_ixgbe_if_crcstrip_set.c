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
struct ixgbe_hw {int dummy; } ;
struct adapter {struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_HLREG0 ; 
 int /*<<< orphan*/  IXGBE_HLREG0_RXCRCSTRP ; 
 int /*<<< orphan*/  IXGBE_RDRXCTL ; 
 int /*<<< orphan*/  IXGBE_RDRXCTL_CRCSTRIP ; 
 int /*<<< orphan*/  IXGBE_RDRXCTL_RSCACKC ; 
 int /*<<< orphan*/  IXGBE_RDRXCTL_RSCFRSTSIZE ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ netmap_verbose ; 

__attribute__((used)) static void
ixgbe_if_crcstrip_set(if_ctx_t ctx, int onoff, int crcstrip)
{
	struct adapter *sc = iflib_get_softc(ctx);
	struct ixgbe_hw *hw = &sc->hw;
	/* crc stripping is set in two places:
	 * IXGBE_HLREG0 (modified on init_locked and hw reset)
	 * IXGBE_RDRXCTL (set by the original driver in
	 *	ixgbe_setup_hw_rsc() called in init_locked.
	 *	We disable the setting when netmap is compiled in).
	 * We update the values here, but also in ixgbe.c because
	 * init_locked sometimes is called outside our control.
	 */
	uint32_t hl, rxc;

	hl = IXGBE_READ_REG(hw, IXGBE_HLREG0);
	rxc = IXGBE_READ_REG(hw, IXGBE_RDRXCTL);
#ifdef NETMAP
	if (netmap_verbose)
		D("%s read  HLREG 0x%x rxc 0x%x",
			onoff ? "enter" : "exit", hl, rxc);
#endif
	/* hw requirements ... */
	rxc &= ~IXGBE_RDRXCTL_RSCFRSTSIZE;
	rxc |= IXGBE_RDRXCTL_RSCACKC;
	if (onoff && !crcstrip) {
		/* keep the crc. Fast rx */
		hl &= ~IXGBE_HLREG0_RXCRCSTRP;
		rxc &= ~IXGBE_RDRXCTL_CRCSTRIP;
	} else {
		/* reset default mode */
		hl |= IXGBE_HLREG0_RXCRCSTRP;
		rxc |= IXGBE_RDRXCTL_CRCSTRIP;
	}
#ifdef NETMAP
	if (netmap_verbose)
		D("%s write HLREG 0x%x rxc 0x%x",
			onoff ? "enter" : "exit", hl, rxc);
#endif
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hl);
	IXGBE_WRITE_REG(hw, IXGBE_RDRXCTL, rxc);
}