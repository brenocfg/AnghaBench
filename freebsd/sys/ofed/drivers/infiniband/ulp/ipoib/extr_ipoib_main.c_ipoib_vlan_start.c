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
struct ipoib_dev_priv {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* VLAN_COOKIE (struct ifnet*) ; 
 void _ipoib_start (struct ifnet*,struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
ipoib_vlan_start(struct ifnet *dev)
{
	struct ipoib_dev_priv *priv;
	struct mbuf *mb;

	priv = VLAN_COOKIE(dev);
	if (priv != NULL)
		return _ipoib_start(dev, priv);
	while (!IFQ_DRV_IS_EMPTY(&dev->if_snd)) {
		IFQ_DRV_DEQUEUE(&dev->if_snd, mb);
		if (mb == NULL)
			break;
		m_freem(mb);
		if_inc_counter(dev, IFCOUNTER_OERRORS, 1);
	}
}