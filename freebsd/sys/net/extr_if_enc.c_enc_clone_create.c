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
struct ifnet {struct enc_softc* if_softc; int /*<<< orphan*/  if_output; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_mtu; } ;
struct if_clone {int dummy; } ;
struct enchdr {int dummy; } ;
struct enc_softc {struct ifnet* sc_ifp; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_ENC ; 
 int EEXIST ; 
 int /*<<< orphan*/  ENCMTU ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IFT_ENC ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct enc_softc* V_enc_sc ; 
 int /*<<< orphan*/  bpfattach (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enc_ioctl ; 
 int /*<<< orphan*/  enc_output ; 
 int /*<<< orphan*/  encname ; 
 int /*<<< orphan*/  free (struct enc_softc*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 struct enc_softc* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
enc_clone_create(struct if_clone *ifc, int unit, caddr_t params)
{
	struct ifnet *ifp;
	struct enc_softc *sc;

	sc = malloc(sizeof(struct enc_softc), M_DEVBUF,
	    M_WAITOK | M_ZERO);
	ifp = sc->sc_ifp = if_alloc(IFT_ENC);
	if (ifp == NULL) {
		free(sc, M_DEVBUF);
		return (ENOSPC);
	}
	if (V_enc_sc != NULL) {
		if_free(ifp);
		free(sc, M_DEVBUF);
		return (EEXIST);
	}
	V_enc_sc = sc;
	if_initname(ifp, encname, unit);
	ifp->if_mtu = ENCMTU;
	ifp->if_ioctl = enc_ioctl;
	ifp->if_output = enc_output;
	ifp->if_softc = sc;
	if_attach(ifp);
	bpfattach(ifp, DLT_ENC, sizeof(struct enchdr));
	return (0);
}