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
struct TYPE_4__ {struct ifnet* rcvif; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct ifqueue {int dummy; } ;
struct TYPE_3__ {struct ipoib_ah* raw; } ;
struct ib_sa_path_rec {char* sl; int /*<<< orphan*/  dlid; TYPE_1__ dgid; } ;
struct ipoib_path {int valid; int /*<<< orphan*/  done; int /*<<< orphan*/ * query; int /*<<< orphan*/  hwaddr; struct ifqueue queue; struct ipoib_ah* ah; struct ib_sa_path_rec pathrec; struct ipoib_dev_priv* priv; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  pd; int /*<<< orphan*/  port; int /*<<< orphan*/  ca; struct ifnet* dev; } ;
struct ipoib_ah {int dummy; } ;
struct ifnet {scalar_t__ (* if_transmit ) (struct ifnet*,struct mbuf*) ;} ;
struct ib_ah_attr {int dummy; } ;
struct epoch_tracker {int dummy; } ;
typedef  int /*<<< orphan*/  mbqueue ;

/* Variables and functions */
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  _IF_DEQUEUE (struct ifqueue*,struct mbuf*) ; 
 int /*<<< orphan*/  _IF_ENQUEUE (struct ifqueue*,struct mbuf*) ; 
 struct ipoib_ah* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct ifqueue*,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_init_ah_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_sa_path_rec*,struct ib_ah_attr*) ; 
 int /*<<< orphan*/  ipoib_cm_create_tx (struct ipoib_dev_priv*,struct ipoib_path*) ; 
 scalar_t__ ipoib_cm_enabled (struct ipoib_dev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_cm_get (struct ipoib_path*) ; 
 int /*<<< orphan*/  ipoib_cm_set (struct ipoib_path*,int /*<<< orphan*/ ) ; 
 struct ipoib_ah* ipoib_create_ah (struct ipoib_dev_priv*,int /*<<< orphan*/ ,struct ib_ah_attr*) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,int,struct ipoib_ah*,char*) ; 
 int /*<<< orphan*/  ipoib_put_ah (struct ipoib_ah*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static void
path_rec_completion(int status, struct ib_sa_path_rec *pathrec, void *path_ptr)
{
	struct ipoib_path *path = path_ptr;
	struct ipoib_dev_priv *priv = path->priv;
	struct ifnet *dev = priv->dev;
	struct ipoib_ah *ah = NULL;
	struct ipoib_ah *old_ah = NULL;
	struct epoch_tracker et;
	struct ifqueue mbqueue;
	struct mbuf *mb;
	unsigned long flags;

	if (!status)
		ipoib_dbg(priv, "PathRec LID 0x%04x for GID %16D\n",
			  be16_to_cpu(pathrec->dlid), pathrec->dgid.raw, ":");
	else
		ipoib_dbg(priv, "PathRec status %d for GID %16D\n",
			  status, path->pathrec.dgid.raw, ":");

	bzero(&mbqueue, sizeof(mbqueue));

	if (!status) {
		struct ib_ah_attr av;

		if (!ib_init_ah_from_path(priv->ca, priv->port, pathrec, &av))
			ah = ipoib_create_ah(priv, priv->pd, &av);
	}

	spin_lock_irqsave(&priv->lock, flags);

	if (ah) {
		path->pathrec = *pathrec;

		old_ah   = path->ah;
		path->ah = ah;

		ipoib_dbg(priv, "created address handle %p for LID 0x%04x, SL %d\n",
			  ah, be16_to_cpu(pathrec->dlid), pathrec->sl);

		for (;;) {
			_IF_DEQUEUE(&path->queue, mb);
			if (mb == NULL)
				break;
			_IF_ENQUEUE(&mbqueue, mb);
		}

#ifdef CONFIG_INFINIBAND_IPOIB_CM
		if (ipoib_cm_enabled(priv, path->hwaddr) && !ipoib_cm_get(path))
			ipoib_cm_set(path, ipoib_cm_create_tx(priv, path));
#endif

		path->valid = 1;
	}

	path->query = NULL;
	complete(&path->done);

	spin_unlock_irqrestore(&priv->lock, flags);

	if (old_ah)
		ipoib_put_ah(old_ah);

	NET_EPOCH_ENTER(et);
	for (;;) {
		_IF_DEQUEUE(&mbqueue, mb);
		if (mb == NULL)
			break;
		mb->m_pkthdr.rcvif = dev;
		if (dev->if_transmit(dev, mb))
			ipoib_warn(priv, "dev_queue_xmit failed "
				   "to requeue packet\n");
	}
	NET_EPOCH_EXIT(et);
}