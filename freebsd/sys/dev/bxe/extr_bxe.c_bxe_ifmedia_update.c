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
struct ifnet {int dummy; } ;
struct ifmedia {int /*<<< orphan*/  ifm_media; } ;
struct bxe_softc {struct ifmedia ifmedia; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int EINVAL ; 
#define  IFM_10G_CX4 132 
#define  IFM_10G_SR 131 
#define  IFM_10G_T 130 
#define  IFM_10G_TWINAX 129 
#define  IFM_AUTO 128 
 scalar_t__ IFM_ETHER ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ IFM_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ if_getsoftc (struct ifnet*) ; 

__attribute__((used)) static int
bxe_ifmedia_update(struct ifnet  *ifp)
{
    struct bxe_softc *sc = (struct bxe_softc *)if_getsoftc(ifp);
    struct ifmedia *ifm;

    ifm = &sc->ifmedia;

    /* We only support Ethernet media type. */
    if (IFM_TYPE(ifm->ifm_media) != IFM_ETHER) {
        return (EINVAL);
    }

    switch (IFM_SUBTYPE(ifm->ifm_media)) {
    case IFM_AUTO:
         break;
    case IFM_10G_CX4:
    case IFM_10G_SR:
    case IFM_10G_T:
    case IFM_10G_TWINAX:
    default:
        /* We don't support changing the media type. */
        BLOGD(sc, DBG_LOAD, "Invalid media type (%d)\n",
              IFM_SUBTYPE(ifm->ifm_media));
        return (EINVAL);
    }

    return (0);
}