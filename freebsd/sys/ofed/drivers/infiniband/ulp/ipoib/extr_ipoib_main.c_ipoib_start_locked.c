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
struct mbuf {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPOIB_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_send_one (struct ipoib_dev_priv*,struct mbuf*) ; 

void
ipoib_start_locked(struct ifnet *dev, struct ipoib_dev_priv *priv)
{
	struct mbuf *mb;

	assert_spin_locked(&priv->lock);

	while (!IFQ_DRV_IS_EMPTY(&dev->if_snd) &&
	    (dev->if_drv_flags & IFF_DRV_OACTIVE) == 0) {
		IFQ_DRV_DEQUEUE(&dev->if_snd, mb);
		if (mb == NULL)
			break;
		IPOIB_MTAP(dev, mb);
		ipoib_send_one(priv, mb);
	}
}