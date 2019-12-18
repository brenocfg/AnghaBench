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
struct ifnet {struct enc_softc* if_softc; } ;
struct enc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 struct enc_softc* V_enc_sc ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct enc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 

__attribute__((used)) static void
enc_clone_destroy(struct ifnet *ifp)
{
	struct enc_softc *sc;

	sc = ifp->if_softc;
	KASSERT(sc == V_enc_sc, ("sc != ifp->if_softc"));

	bpfdetach(ifp);
	if_detach(ifp);
	if_free(ifp);
	free(sc, M_DEVBUF);
	V_enc_sc = NULL;
}