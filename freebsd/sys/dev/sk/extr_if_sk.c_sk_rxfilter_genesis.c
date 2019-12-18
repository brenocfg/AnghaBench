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
typedef  int /*<<< orphan*/  u_int16_t ;
struct sk_if_softc {struct ifnet* sk_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct sk_add_maddr_genesis_ctx {int mode; int* hashes; TYPE_1__ member_1; struct sk_if_softc* member_0; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  SK_IF_LOCK_ASSERT (struct sk_if_softc*) ; 
 int SK_XM_READ_4 (struct sk_if_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SK_XM_WRITE_4 (struct sk_if_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XM_MAR0 ; 
 int /*<<< orphan*/  XM_MAR2 ; 
 int /*<<< orphan*/  XM_MODE ; 
 int XM_MODE_RX_PROMISC ; 
 int XM_MODE_RX_USE_HASH ; 
 int XM_MODE_RX_USE_PERFECT ; 
 int XM_RXFILT_MAX ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct sk_add_maddr_genesis_ctx*) ; 
 int /*<<< orphan*/  sk_add_maddr_genesis ; 
 int /*<<< orphan*/  sk_setfilt (struct sk_if_softc*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
sk_rxfilter_genesis(struct sk_if_softc *sc_if)
{
	struct ifnet		*ifp = sc_if->sk_ifp;
	struct sk_add_maddr_genesis_ctx ctx = { sc_if, { 0, 0 } };
	int			i;
	u_int16_t		dummy[] = { 0, 0, 0 };

	SK_IF_LOCK_ASSERT(sc_if);

	ctx.mode = SK_XM_READ_4(sc_if, XM_MODE);
	ctx.mode &= ~(XM_MODE_RX_PROMISC | XM_MODE_RX_USE_HASH |
	    XM_MODE_RX_USE_PERFECT);
	/* First, zot all the existing perfect filters. */
	for (i = 1; i < XM_RXFILT_MAX; i++)
		sk_setfilt(sc_if, dummy, i);

	/* Now program new ones. */
	if (ifp->if_flags & IFF_ALLMULTI || ifp->if_flags & IFF_PROMISC) {
		if (ifp->if_flags & IFF_ALLMULTI)
			ctx.mode |= XM_MODE_RX_USE_HASH;
		if (ifp->if_flags & IFF_PROMISC)
			ctx.mode |= XM_MODE_RX_PROMISC;
		ctx.hashes[0] = 0xFFFFFFFF;
		ctx.hashes[1] = 0xFFFFFFFF;
	} else
		/* XXX want to maintain reverse semantics */
		if_foreach_llmaddr(ifp, sk_add_maddr_genesis, &ctx);

	SK_XM_WRITE_4(sc_if, XM_MODE, ctx.mode);
	SK_XM_WRITE_4(sc_if, XM_MAR0, ctx.hashes[0]);
	SK_XM_WRITE_4(sc_if, XM_MAR2, ctx.hashes[1]);
}