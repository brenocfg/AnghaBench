#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_8__ {TYPE_1__ sin6; TYPE_3__ sin; } ;
struct secasindex {TYPE_4__ src; } ;
struct ipsec_softc {int family; TYPE_2__* ifp; } ;
struct TYPE_6__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IPSEC_DIR_OUTBOUND ; 
 int in6_localip (int /*<<< orphan*/ *) ; 
 int in_localip (int /*<<< orphan*/ ) ; 
 struct secasindex* ipsec_getsaidx (struct ipsec_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ipsec_set_running(struct ipsec_softc *sc)
{
	struct secasindex *saidx;
	int localip;

	saidx = ipsec_getsaidx(sc, IPSEC_DIR_OUTBOUND, sc->family);
	localip = 0;
	switch (sc->family) {
#ifdef INET
	case AF_INET:
		localip = in_localip(saidx->src.sin.sin_addr);
		break;
#endif
#ifdef INET6
	case AF_INET6:
		localip = in6_localip(&saidx->src.sin6.sin6_addr);
		break;
#endif
	}
	if (localip != 0)
		sc->ifp->if_drv_flags |= IFF_DRV_RUNNING;
	else
		sc->ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
}