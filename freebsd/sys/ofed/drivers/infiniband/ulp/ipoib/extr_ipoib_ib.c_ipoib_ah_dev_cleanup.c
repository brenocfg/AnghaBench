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
struct ipoib_dev_priv {int /*<<< orphan*/  dead_ahs; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  __ipoib_reap_ah (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static void ipoib_ah_dev_cleanup(struct ipoib_dev_priv *priv)
{
	unsigned long begin;

	begin = jiffies;

	while (!list_empty(&priv->dead_ahs)) {
		__ipoib_reap_ah(priv);

		if (time_after(jiffies, begin + HZ)) {
			ipoib_warn(priv, "timing out; will leak address handles\n");
			break;
		}

		msleep(1);
	}
}