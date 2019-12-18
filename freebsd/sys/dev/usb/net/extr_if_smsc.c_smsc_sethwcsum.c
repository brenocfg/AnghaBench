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
struct smsc_softc {int /*<<< orphan*/  sc_ue; } ;
struct ifnet {int if_capabilities; int if_capenable; } ;

/* Variables and functions */
 int EIO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TXCSUM ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SMSC_COE_CTRL ; 
 int /*<<< orphan*/  SMSC_COE_CTRL_RX_EN ; 
 int /*<<< orphan*/  SMSC_COE_CTRL_TX_EN ; 
 int /*<<< orphan*/  SMSC_LOCK_ASSERT (struct smsc_softc*,int /*<<< orphan*/ ) ; 
 int smsc_read_reg (struct smsc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsc_warn_printf (struct smsc_softc*,char*,int) ; 
 int smsc_write_reg (struct smsc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smsc_sethwcsum(struct smsc_softc *sc)
{
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	uint32_t val;
	int err;

	if (!ifp)
		return (-EIO);

	SMSC_LOCK_ASSERT(sc, MA_OWNED);

	err = smsc_read_reg(sc, SMSC_COE_CTRL, &val);
	if (err != 0) {
		smsc_warn_printf(sc, "failed to read SMSC_COE_CTRL (err=%d)\n", err);
		return (err);
	}

	/* Enable/disable the Rx checksum */
	if ((ifp->if_capabilities & ifp->if_capenable) & IFCAP_RXCSUM)
		val |= SMSC_COE_CTRL_RX_EN;
	else
		val &= ~SMSC_COE_CTRL_RX_EN;

	/* Enable/disable the Tx checksum (currently not supported) */
	if ((ifp->if_capabilities & ifp->if_capenable) & IFCAP_TXCSUM)
		val |= SMSC_COE_CTRL_TX_EN;
	else
		val &= ~SMSC_COE_CTRL_TX_EN;

	err = smsc_write_reg(sc, SMSC_COE_CTRL, val);
	if (err != 0) {
		smsc_warn_printf(sc, "failed to write SMSC_COE_CTRL (err=%d)\n", err);
		return (err);
	}

	return (0);
}