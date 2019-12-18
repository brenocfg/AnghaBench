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
struct ifnet {void* if_baudrate; int /*<<< orphan*/  if_softc; } ;
struct ifmedia {int ifm_media; } ;
typedef  TYPE_1__* priv_p ;
struct TYPE_2__ {struct ifmedia media; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFM_1000_T ; 
 scalar_t__ IFM_AUTO ; 
 int IFM_ETHER ; 
 scalar_t__ IFM_SUBTYPE (int) ; 
 int IFM_TYPE (int) ; 
 void* ifmedia_baudrate (int) ; 

__attribute__((used)) static int
ng_eiface_mediachange(struct ifnet *ifp)
{
	const priv_p priv = (priv_p)ifp->if_softc;
	struct ifmedia *ifm = &priv->media;

	if (IFM_TYPE(ifm->ifm_media) != IFM_ETHER)
		return (EINVAL);
	if (IFM_SUBTYPE(ifm->ifm_media) == IFM_AUTO)
		ifp->if_baudrate = ifmedia_baudrate(IFM_ETHER | IFM_1000_T);
	else
		ifp->if_baudrate = ifmedia_baudrate(ifm->ifm_media);

	return (0);
}