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
struct iavf_sc {int /*<<< orphan*/  promisc_flags; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_VF_MULTICAST_PROMISC ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_ADD_MAC_FILTER ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_CONFIGURE_PROMISC ; 
 int /*<<< orphan*/  IOCTL_DEBUGOUT (char*) ; 
 scalar_t__ MAX_MULTICAST_ADDR ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  iavf_init_multi (struct iavf_sc*) ; 
 int /*<<< orphan*/  iavf_mc_filter_apply ; 
 int /*<<< orphan*/  iavf_send_vc_msg (struct iavf_sc*,int /*<<< orphan*/ ) ; 
 scalar_t__ if_foreach_llmaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iavf_sc*) ; 
 scalar_t__ if_llmaddr_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct iavf_sc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iavf_if_multi_set(if_ctx_t ctx)
{
	struct iavf_sc *sc = iflib_get_softc(ctx);

	IOCTL_DEBUGOUT("iavf_if_multi_set: begin");

	if (__predict_false(if_llmaddr_count(iflib_get_ifp(ctx)) >=
	    MAX_MULTICAST_ADDR)) {
		/* Delete MC filters and enable mulitcast promisc instead */
		iavf_init_multi(sc);
		sc->promisc_flags |= FLAG_VF_MULTICAST_PROMISC;
		iavf_send_vc_msg(sc, IAVF_FLAG_AQ_CONFIGURE_PROMISC);
		return;
	}

	/* If there aren't too many filters, delete existing MC filters */
	iavf_init_multi(sc);

	/* And (re-)install filters for all mcast addresses */
	if (if_foreach_llmaddr(iflib_get_ifp(ctx), iavf_mc_filter_apply, sc) >
	    0)
		iavf_send_vc_msg(sc, IAVF_FLAG_AQ_ADD_MAC_FILTER);
}