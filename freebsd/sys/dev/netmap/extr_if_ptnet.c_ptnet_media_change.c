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
struct ptnet_softc {struct ifmedia media; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IFM_ETHER ; 
 scalar_t__ IFM_TYPE (int /*<<< orphan*/ ) ; 
 struct ptnet_softc* if_getsoftc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ptnet_media_change(if_t ifp)
{
	struct ptnet_softc *sc = if_getsoftc(ifp);
	struct ifmedia *ifm = &sc->media;

	if (IFM_TYPE(ifm->ifm_media) != IFM_ETHER) {
		return EINVAL;
	}

	return 0;
}