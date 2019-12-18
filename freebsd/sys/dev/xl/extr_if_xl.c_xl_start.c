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
struct xl_softc {scalar_t__ xl_type; } ;
struct ifnet {struct xl_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  XL_LOCK (struct xl_softc*) ; 
 scalar_t__ XL_TYPE_905B ; 
 int /*<<< orphan*/  XL_UNLOCK (struct xl_softc*) ; 
 int /*<<< orphan*/  xl_start_90xB_locked (struct ifnet*) ; 
 int /*<<< orphan*/  xl_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
xl_start(struct ifnet *ifp)
{
	struct xl_softc		*sc = ifp->if_softc;

	XL_LOCK(sc);

	if (sc->xl_type == XL_TYPE_905B)
		xl_start_90xB_locked(ifp);
	else
		xl_start_locked(ifp);

	XL_UNLOCK(sc);
}