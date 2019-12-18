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
typedef  union ib_gid {int dummy; } ib_gid ;
struct mbuf {int dummy; } ;
struct TYPE_8__ {scalar_t__ ifq_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  raw; } ;
struct TYPE_7__ {TYPE_2__ mgid; } ;
struct ipoib_mcast {scalar_t__ ah; int /*<<< orphan*/  flags; TYPE_4__ pkt_queue; int /*<<< orphan*/  list; TYPE_3__ mcmember; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  multicast_list; TYPE_1__* broadcast; int /*<<< orphan*/  flags; struct ifnet* dev; } ;
struct ifnet {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MULTICAST_QPN ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IPOIB_FLAG_OPER_UP ; 
 scalar_t__ IPOIB_MAX_MCAST_QUEUE ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_ATTACHED ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_BUSY ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_SENDONLY ; 
 int /*<<< orphan*/  _IF_ENQUEUE (TYPE_4__*,struct mbuf*) ; 
 int /*<<< orphan*/  __ipoib_mcast_add (struct ipoib_dev_priv*,struct ipoib_mcast*) ; 
 struct ipoib_mcast* __ipoib_mcast_find (struct ipoib_dev_priv*,void*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (struct ipoib_dev_priv*,char*,...) ; 
 struct ipoib_mcast* ipoib_mcast_alloc (struct ipoib_dev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_mcast_sendonly_join (struct ipoib_mcast*) ; 
 int /*<<< orphan*/  ipoib_send (struct ipoib_dev_priv*,struct mbuf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ipoib_mcast_send(struct ipoib_dev_priv *priv, void *mgid, struct mbuf *mb)
{
	struct ifnet *dev = priv->dev;
	struct ipoib_mcast *mcast;

	if (!test_bit(IPOIB_FLAG_OPER_UP, &priv->flags)		||
	    !priv->broadcast					||
	    !test_bit(IPOIB_MCAST_FLAG_ATTACHED, &priv->broadcast->flags)) {
		if_inc_counter(dev, IFCOUNTER_OERRORS, 1);
		m_freem(mb);
		return;
	}

	mcast = __ipoib_mcast_find(priv, mgid);
	if (!mcast) {
		/* Let's create a new send only group now */
		ipoib_dbg_mcast(priv, "setting up send only multicast group for %16D\n",
				mgid, ":");

		mcast = ipoib_mcast_alloc(priv, 0);
		if (!mcast) {
			ipoib_warn(priv, "unable to allocate memory for "
				   "multicast structure\n");
			if_inc_counter(dev, IFCOUNTER_OERRORS, 1);
			m_freem(mb);
			goto out;
		}

		set_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags);
		memcpy(mcast->mcmember.mgid.raw, mgid, sizeof (union ib_gid));
		__ipoib_mcast_add(priv, mcast);
		list_add_tail(&mcast->list, &priv->multicast_list);
	}

	if (!mcast->ah) {
		if (mcast->pkt_queue.ifq_len < IPOIB_MAX_MCAST_QUEUE) {
			_IF_ENQUEUE(&mcast->pkt_queue, mb);
		} else {
			if_inc_counter(dev, IFCOUNTER_OERRORS, 1);
			m_freem(mb);
		}

		if (test_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags))
			ipoib_dbg_mcast(priv, "no address vector, "
					"but multicast join already started\n");
		else if (test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags))
			ipoib_mcast_sendonly_join(mcast);

		/*
		 * If lookup completes between here and out:, don't
		 * want to send packet twice.
		 */
		mcast = NULL;
	}

out:
	if (mcast && mcast->ah)
		ipoib_send(priv, mb, mcast->ah, IB_MULTICAST_QPN);
}