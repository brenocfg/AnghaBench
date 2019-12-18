#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ifm_media; } ;
struct llan_softc {TYPE_1__ media; } ;
struct ifnet {struct llan_softc* if_softc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IFM_AUTO ; 
 scalar_t__ IFM_ETHER ; 
 scalar_t__ IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ IFM_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
llan_media_change(struct ifnet *ifp)
{
	struct llan_softc *sc = ifp->if_softc;

	if (IFM_TYPE(sc->media.ifm_media) != IFM_ETHER)
		return (EINVAL);

	if (IFM_SUBTYPE(sc->media.ifm_media) != IFM_AUTO)
		return (EINVAL);

	return (0);
}