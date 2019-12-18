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
struct ipoib_dev_priv {int pkey; int /*<<< orphan*/  flags; int /*<<< orphan*/  ah_reap_task; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  port; int /*<<< orphan*/  ca; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IPOIB_FLAG_INITIALIZED ; 
 int /*<<< orphan*/  IPOIB_PKEY_ASSIGNED ; 
 int /*<<< orphan*/  IPOIB_STOP_REAPER ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ib_find_pkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int ipoib_cm_dev_open (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  ipoib_ib_dev_stop (struct ipoib_dev_priv*,int) ; 
 int ipoib_ib_post_receives (struct ipoib_dev_priv*) ; 
 int ipoib_init_qp (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ipoib_ib_dev_open(struct ipoib_dev_priv *priv)
{
	int ret;

	if (ib_find_pkey(priv->ca, priv->port, priv->pkey, &priv->pkey_index)) {
		ipoib_warn(priv, "P_Key 0x%04x not found\n", priv->pkey);
		clear_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);
		return -1;
	}
	set_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);

	ret = ipoib_init_qp(priv);
	if (ret) {
		ipoib_warn(priv, "ipoib_init_qp returned %d\n", ret);
		return -1;
	}

	ret = ipoib_ib_post_receives(priv);
	if (ret) {
		ipoib_warn(priv, "ipoib_ib_post_receives returned %d\n", ret);
		ipoib_ib_dev_stop(priv, 1);
		return -1;
	}

	ret = ipoib_cm_dev_open(priv);
	if (ret) {
		ipoib_warn(priv, "ipoib_cm_dev_open returned %d\n", ret);
		ipoib_ib_dev_stop(priv, 1);
		return -1;
	}

	clear_bit(IPOIB_STOP_REAPER, &priv->flags);
	queue_delayed_work(ipoib_workqueue, &priv->ah_reap_task, HZ);

	set_bit(IPOIB_FLAG_INITIALIZED, &priv->flags);

	return 0;
}