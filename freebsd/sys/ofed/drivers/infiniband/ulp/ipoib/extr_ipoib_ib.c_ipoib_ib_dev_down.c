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
struct ipoib_dev_priv {int /*<<< orphan*/  pkey_poll_task; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_FLAG_OPER_UP ; 
 int /*<<< orphan*/  IPOIB_PKEY_ASSIGNED ; 
 int /*<<< orphan*/  IPOIB_PKEY_STOP ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_flush_paths (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  ipoib_mcast_dev_flush (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  ipoib_mcast_stop_thread (struct ipoib_dev_priv*,int) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkey_mutex ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ipoib_ib_dev_down(struct ipoib_dev_priv *priv, int flush)
{

	ipoib_dbg(priv, "downing ib_dev\n");

	clear_bit(IPOIB_FLAG_OPER_UP, &priv->flags);
	if_link_state_change(priv->dev, LINK_STATE_DOWN);

	/* Shutdown the P_Key thread if still active */
	if (!test_bit(IPOIB_PKEY_ASSIGNED, &priv->flags)) {
		mutex_lock(&pkey_mutex);
		set_bit(IPOIB_PKEY_STOP, &priv->flags);
		cancel_delayed_work(&priv->pkey_poll_task);
		mutex_unlock(&pkey_mutex);
		if (flush)
			flush_workqueue(ipoib_workqueue);
	}

	ipoib_mcast_stop_thread(priv, flush);
	ipoib_mcast_dev_flush(priv);

	ipoib_flush_paths(priv);

	return 0;
}