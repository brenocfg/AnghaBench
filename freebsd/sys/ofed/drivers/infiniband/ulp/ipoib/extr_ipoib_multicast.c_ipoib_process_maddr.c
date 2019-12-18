#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union ib_gid {int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
struct sockaddr_dl {int sdl_alen; } ;
struct ipoib_mcast_ctx {int /*<<< orphan*/  remove_list; struct ipoib_dev_priv* priv; } ;
struct TYPE_4__ {union ib_gid mgid; } ;
struct ipoib_mcast {int /*<<< orphan*/  flags; int /*<<< orphan*/  list; int /*<<< orphan*/  rb_node; TYPE_2__ mcmember; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  multicast_list; int /*<<< orphan*/  multicast_tree; int /*<<< orphan*/  port; int /*<<< orphan*/  ca; int /*<<< orphan*/  flags; TYPE_1__* dev; } ;
struct ib_sa_mcmember_rec {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_broadcastaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_FLAG_UMCAST ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_FOUND ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_SENDONLY ; 
 int /*<<< orphan*/ * LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  __ipoib_mcast_add (struct ipoib_dev_priv*,struct ipoib_mcast*) ; 
 struct ipoib_mcast* __ipoib_mcast_find (struct ipoib_dev_priv*,union ib_gid*) ; 
 int /*<<< orphan*/  ib_sa_get_mcmember_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ib_gid*,struct ib_sa_mcmember_rec*) ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ipoib_mcast_addr_is_valid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct ipoib_mcast* ipoib_mcast_alloc (struct ipoib_dev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rb_replace_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_int
ipoib_process_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct ipoib_mcast_ctx *ctx = arg;
	struct ipoib_dev_priv *priv = ctx->priv;
	struct ipoib_mcast *mcast;
	struct ib_sa_mcmember_rec rec;
	union ib_gid mgid;
	uint8_t *addr;
	int addrlen;

	addr = LLADDR(sdl);
	addrlen = sdl->sdl_alen;
	if (!ipoib_mcast_addr_is_valid(addr, addrlen,
	    priv->dev->if_broadcastaddr))
		return (0);

	memcpy(mgid.raw, addr + 4, sizeof mgid);

	mcast = __ipoib_mcast_find(priv, &mgid);
	if (!mcast || test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags)) {
		struct ipoib_mcast *nmcast;

		/* ignore group which is directly joined by userspace */
		if (test_bit(IPOIB_FLAG_UMCAST, &priv->flags) &&
		    !ib_sa_get_mcmember_rec(priv->ca, priv->port, &mgid, &rec)) {
			ipoib_dbg_mcast(priv, "ignoring multicast entry for mgid %16D\n",
					mgid.raw, ":");
			return (0);
		}

		/* Not found or send-only group, let's add a new entry */
		ipoib_dbg_mcast(priv, "adding multicast entry for mgid %16D\n",
				mgid.raw, ":");

		nmcast = ipoib_mcast_alloc(priv, 0);
		if (!nmcast) {
			ipoib_warn(priv, "unable to allocate memory for multicast structure\n");
			return (0);
		}

		set_bit(IPOIB_MCAST_FLAG_FOUND, &nmcast->flags);

		nmcast->mcmember.mgid = mgid;

		if (mcast) {
			/* Destroy the send only entry */
			list_move_tail(&mcast->list, &ctx->remove_list);

			rb_replace_node(&mcast->rb_node,
					&nmcast->rb_node,
					&priv->multicast_tree);
		} else
			__ipoib_mcast_add(priv, nmcast);

		list_add_tail(&nmcast->list, &priv->multicast_list);
	}

	if (mcast)
		set_bit(IPOIB_MCAST_FLAG_FOUND, &mcast->flags);

	return (1);
}