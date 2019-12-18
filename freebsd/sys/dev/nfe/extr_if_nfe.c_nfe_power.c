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
typedef  int uint32_t ;
struct nfe_softc {int nfe_flags; int nfe_revid; scalar_t__ nfe_devid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  NFE_MAC_RESET ; 
 int NFE_MAC_RESET_MAGIC ; 
 int /*<<< orphan*/  NFE_PWR2_CTL ; 
 int NFE_PWR2_REVA3 ; 
 int NFE_PWR2_WAKEUP_MASK ; 
 int NFE_PWR_MGMT ; 
 int NFE_READ (struct nfe_softc*,int /*<<< orphan*/ ) ; 
 int NFE_RXTX_BIT2 ; 
 int /*<<< orphan*/  NFE_RXTX_CTL ; 
 int NFE_RXTX_RESET ; 
 int /*<<< orphan*/  NFE_WRITE (struct nfe_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PCI_PRODUCT_NVIDIA_NFORCE430_LAN1 ; 
 scalar_t__ PCI_PRODUCT_NVIDIA_NFORCE430_LAN2 ; 

__attribute__((used)) static void
nfe_power(struct nfe_softc *sc)
{
	uint32_t pwr;

	if ((sc->nfe_flags & NFE_PWR_MGMT) == 0)
		return;
	NFE_WRITE(sc, NFE_RXTX_CTL, NFE_RXTX_RESET | NFE_RXTX_BIT2);
	NFE_WRITE(sc, NFE_MAC_RESET, NFE_MAC_RESET_MAGIC);
	DELAY(100);
	NFE_WRITE(sc, NFE_MAC_RESET, 0);
	DELAY(100);
	NFE_WRITE(sc, NFE_RXTX_CTL, NFE_RXTX_BIT2);
	pwr = NFE_READ(sc, NFE_PWR2_CTL);
	pwr &= ~NFE_PWR2_WAKEUP_MASK;
	if (sc->nfe_revid >= 0xa3 &&
	    (sc->nfe_devid == PCI_PRODUCT_NVIDIA_NFORCE430_LAN1 ||
	    sc->nfe_devid == PCI_PRODUCT_NVIDIA_NFORCE430_LAN2))
		pwr |= NFE_PWR2_REVA3;
	NFE_WRITE(sc, NFE_PWR2_CTL, pwr);
}