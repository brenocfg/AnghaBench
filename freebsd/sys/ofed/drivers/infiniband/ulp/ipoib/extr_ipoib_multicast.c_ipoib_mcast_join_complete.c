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
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;
struct TYPE_4__ {TYPE_1__ mgid; } ;
struct ipoib_mcast {int backoff; int /*<<< orphan*/  flags; TYPE_2__ mcmember; int /*<<< orphan*/  logcount; struct ipoib_dev_priv* priv; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  mcast_task; int /*<<< orphan*/  flags; int /*<<< orphan*/  carrier_on_task; struct ipoib_mcast* broadcast; } ;
struct ib_sa_multicast {int /*<<< orphan*/  rec; struct ipoib_mcast* context; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENETRESET ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int IPOIB_MAX_BACKOFF_SECONDS ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_BUSY ; 
 int /*<<< orphan*/  IPOIB_MCAST_RUN ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ,char*,int) ; 
 int ipoib_mcast_join_finish (struct ipoib_mcast*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 int /*<<< orphan*/  mcast_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_mcast_join_complete(int status,
				     struct ib_sa_multicast *multicast)
{
	struct ipoib_mcast *mcast = multicast->context;
	struct ipoib_dev_priv *priv = mcast->priv;

	ipoib_dbg_mcast(priv, "join completion for %16D (status %d)\n",
			mcast->mcmember.mgid.raw, ":", status);

	/* We trap for port events ourselves. */
	if (status == -ENETRESET)
		return 0;

	if (!status)
		status = ipoib_mcast_join_finish(mcast, &multicast->rec);

	if (!status) {
		mcast->backoff = 1;
		mutex_lock(&mcast_mutex);
		if (test_bit(IPOIB_MCAST_RUN, &priv->flags))
			queue_delayed_work(ipoib_workqueue,
					   &priv->mcast_task, 0);
		mutex_unlock(&mcast_mutex);

		/*
		 * Defer carrier on work to ipoib_workqueue to avoid a
		 * deadlock on rtnl_lock here.
		 */
		if (mcast == priv->broadcast)
			queue_work(ipoib_workqueue, &priv->carrier_on_task);

		return 0;
	}

	if (mcast->logcount++ < 20) {
		if (status == -ETIMEDOUT || status == -EAGAIN) {
			ipoib_dbg_mcast(priv, "multicast join failed for %16D, status %d\n",
					mcast->mcmember.mgid.raw, ":", status);
		} else {
			ipoib_warn(priv, "multicast join failed for %16D, status %d\n",
				   mcast->mcmember.mgid.raw, ":", status);
		}
	}

	mcast->backoff *= 2;
	if (mcast->backoff > IPOIB_MAX_BACKOFF_SECONDS)
		mcast->backoff = IPOIB_MAX_BACKOFF_SECONDS;

	/* Clear the busy flag so we try again */
	status = test_and_clear_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags);

	mutex_lock(&mcast_mutex);
	spin_lock_irq(&priv->lock);
	if (test_bit(IPOIB_MCAST_RUN, &priv->flags))
		queue_delayed_work(ipoib_workqueue, &priv->mcast_task,
				   mcast->backoff * HZ);
	spin_unlock_irq(&priv->lock);
	mutex_unlock(&mcast_mutex);

	return status;
}