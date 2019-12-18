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
struct fxp_softc {int /*<<< orphan*/  ifp; struct fxp_cb_mcs* mcsp; } ;
struct fxp_cb_mcs {int mc_cnt; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int IFF_ALLMULTI ; 
 int MAXMCADDR ; 
 int /*<<< orphan*/  fxp_setup_maddr ; 
 int htole16 (int) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fxp_softc*) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setflagbits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fxp_mc_addrs(struct fxp_softc *sc)
{
	struct fxp_cb_mcs *mcsp = sc->mcsp;
	if_t ifp = sc->ifp;

	if ((if_getflags(ifp) & IFF_ALLMULTI) == 0) {
		mcsp->mc_cnt = 0;
		if_foreach_llmaddr(sc->ifp, fxp_setup_maddr, sc);
		if (mcsp->mc_cnt >= MAXMCADDR) {
			if_setflagbits(ifp, IFF_ALLMULTI, 0);
			mcsp->mc_cnt = 0;
		}
	}
	mcsp->mc_cnt = htole16(mcsp->mc_cnt * ETHER_ADDR_LEN);
}