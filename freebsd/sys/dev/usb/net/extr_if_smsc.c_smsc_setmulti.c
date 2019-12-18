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
struct usb_ether {int dummy; } ;
struct smsc_softc {int sc_mac_csr; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SMSC_HASHH ; 
 int /*<<< orphan*/  SMSC_HASHL ; 
 int /*<<< orphan*/  SMSC_LOCK_ASSERT (struct smsc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMSC_MAC_CSR ; 
 int SMSC_MAC_CSR_HPFILT ; 
 int SMSC_MAC_CSR_MCPAS ; 
 int SMSC_MAC_CSR_PRMS ; 
 scalar_t__ if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  smsc_dbg_printf (struct smsc_softc*,char*) ; 
 int /*<<< orphan*/  smsc_hash_maddr ; 
 int /*<<< orphan*/  smsc_write_reg (struct smsc_softc*,int /*<<< orphan*/ ,int) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct smsc_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
smsc_setmulti(struct usb_ether *ue)
{
	struct smsc_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);
	uint32_t hashtbl[2] = { 0, 0 };

	SMSC_LOCK_ASSERT(sc, MA_OWNED);

	if (ifp->if_flags & (IFF_ALLMULTI | IFF_PROMISC)) {
		smsc_dbg_printf(sc, "receive all multicast enabled\n");
		sc->sc_mac_csr |= SMSC_MAC_CSR_MCPAS;
		sc->sc_mac_csr &= ~SMSC_MAC_CSR_HPFILT;
		
	} else {
		if (if_foreach_llmaddr(ifp, smsc_hash_maddr, &hashtbl) > 0) {
			/* We are filtering on a set of address so calculate
			 * hashes of each of the address and set the
			 * corresponding bits in the register.
			 */
			sc->sc_mac_csr |= SMSC_MAC_CSR_HPFILT;
			sc->sc_mac_csr &= ~(SMSC_MAC_CSR_PRMS | SMSC_MAC_CSR_MCPAS);
		} else {
			/* Only receive packets with destination set to
			 * our mac address
			 */
			sc->sc_mac_csr &= ~(SMSC_MAC_CSR_MCPAS | SMSC_MAC_CSR_HPFILT);
		}
		
		/* Debug */
		if (sc->sc_mac_csr & SMSC_MAC_CSR_HPFILT)
			smsc_dbg_printf(sc, "receive select group of macs\n");
		else
			smsc_dbg_printf(sc, "receive own packets only\n");
	}

	/* Write the hash table and mac control registers */
	smsc_write_reg(sc, SMSC_HASHH, hashtbl[1]);
	smsc_write_reg(sc, SMSC_HASHL, hashtbl[0]);
	smsc_write_reg(sc, SMSC_MAC_CSR, sc->sc_mac_csr);
}