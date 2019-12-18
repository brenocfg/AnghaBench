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
typedef  int u_int ;
struct vi_info {int /*<<< orphan*/  viid; struct port_info* pi; } ;
struct sockaddr_dl {int dummy; } ;
struct port_info {struct adapter* adapter; } ;
struct mcaddr_ctx {scalar_t__ rc; size_t i; scalar_t__ del; int /*<<< orphan*/ ** mcaddr; TYPE_1__* ifp; int /*<<< orphan*/  hash; } ;
struct adapter {int /*<<< orphan*/  mbox; } ;
struct TYPE_2__ {struct vi_info* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_IS_MULTICAST (int /*<<< orphan*/ *) ; 
 size_t FW_MAC_EXACT_CHUNK ; 
 int /*<<< orphan*/ * LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ t4_alloc_mac_filt (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
add_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct mcaddr_ctx *ctx = arg;
	struct vi_info *vi = ctx->ifp->if_softc;
	struct port_info *pi = vi->pi;
	struct adapter *sc = pi->adapter;

	if (ctx->rc < 0)
		return (0);

	ctx->mcaddr[ctx->i] = LLADDR(sdl);
	MPASS(ETHER_IS_MULTICAST(ctx->mcaddr[ctx->i]));
	ctx->i++;

	if (ctx->i == FW_MAC_EXACT_CHUNK) {
		ctx->rc = t4_alloc_mac_filt(sc, sc->mbox, vi->viid, ctx->del,
		    ctx->i, ctx->mcaddr, NULL, &ctx->hash, 0);
		if (ctx->rc < 0) {
			int j;

			for (j = 0; j < ctx->i; j++) {
				if_printf(ctx->ifp,
				    "failed to add mc address"
				    " %02x:%02x:%02x:"
				    "%02x:%02x:%02x rc=%d\n",
				    ctx->mcaddr[j][0], ctx->mcaddr[j][1],
				    ctx->mcaddr[j][2], ctx->mcaddr[j][3],
				    ctx->mcaddr[j][4], ctx->mcaddr[j][5],
				    -ctx->rc);
			}
			return (0);
		}
		ctx->del = 0;
		ctx->i = 0;
	}

	return (1);
}