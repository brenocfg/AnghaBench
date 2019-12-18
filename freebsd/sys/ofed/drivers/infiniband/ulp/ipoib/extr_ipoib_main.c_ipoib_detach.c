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
struct ipoib_dev_priv {int gone; struct ifnet* dev; int /*<<< orphan*/  unit; int /*<<< orphan*/  flags; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_FLAG_SUBINTERFACE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  VLAN_SETCOOKIE (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct ipoib_dev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ipoib_unrhdr ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipoib_detach(struct ipoib_dev_priv *priv)
{
	struct ifnet *dev;

	dev = priv->dev;
	if (!test_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags)) {
		priv->gone = 1;
		bpfdetach(dev);
		if_detach(dev);
		if_free(dev);
		free_unr(ipoib_unrhdr, priv->unit);
	} else
		VLAN_SETCOOKIE(priv->dev, NULL);

	free(priv, M_TEMP);
}