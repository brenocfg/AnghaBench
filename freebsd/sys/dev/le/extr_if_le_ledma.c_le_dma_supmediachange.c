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
struct ifmedia {int /*<<< orphan*/  ifm_media; } ;
struct lance_softc {struct ifmedia sc_media; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IFM_10_5 130 
#define  IFM_10_T 129 
#define  IFM_AUTO 128 
 scalar_t__ IFM_ETHER ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ IFM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_dma_setaui (struct lance_softc*) ; 
 int /*<<< orphan*/  le_dma_setutp (struct lance_softc*) ; 

__attribute__((used)) static int
le_dma_supmediachange(struct lance_softc *sc)
{
	struct ifmedia *ifm = &sc->sc_media;

	if (IFM_TYPE(ifm->ifm_media) != IFM_ETHER)
		return (EINVAL);

	/*
	 * Switch to the selected media. If autoselect is set, we don't
	 * really have to do anything. We'll switch to the other media
	 * when we detect loss of carrier.
	 */
	switch (IFM_SUBTYPE(ifm->ifm_media)) {
	case IFM_10_T:
		le_dma_setutp(sc);
		break;

	case IFM_10_5:
		le_dma_setaui(sc);
		break;

	case IFM_AUTO:
		break;

	default:
		return (EINVAL);
	}

	return (0);
}