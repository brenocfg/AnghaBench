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
struct iavf_sc {int /*<<< orphan*/  promisc_flags; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_VF_MULTICAST_PROMISC ; 
 int /*<<< orphan*/  FLAG_VF_UNICAST_PROMISC ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_CONFIGURE_PROMISC ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ MAX_MULTICAST_ADDR ; 
 int /*<<< orphan*/  iavf_send_vc_msg (struct iavf_sc*,int /*<<< orphan*/ ) ; 
 scalar_t__ if_llmaddr_count (struct ifnet*) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct iavf_sc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iavf_if_promisc_set(if_ctx_t ctx, int flags)
{
	struct iavf_sc *sc = iflib_get_softc(ctx);
	struct ifnet	*ifp = iflib_get_ifp(ctx);

	sc->promisc_flags = 0;

	if (flags & IFF_ALLMULTI || if_llmaddr_count(ifp) >=
	    MAX_MULTICAST_ADDR)
		sc->promisc_flags |= FLAG_VF_MULTICAST_PROMISC;
	if (flags & IFF_PROMISC)
		sc->promisc_flags |= FLAG_VF_UNICAST_PROMISC;

	iavf_send_vc_msg(sc, IAVF_FLAG_AQ_CONFIGURE_PROMISC);

	return (0);
}