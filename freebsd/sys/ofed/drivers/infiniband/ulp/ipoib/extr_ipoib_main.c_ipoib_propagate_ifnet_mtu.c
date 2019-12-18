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
struct ipoib_dev_priv {struct ifnet* dev; } ;
struct ifreq {int ifr_mtu; int /*<<< orphan*/  ifr_name; } ;
struct ifnet {int if_mtu; int /*<<< orphan*/  if_vnet; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SIOCSIFMTU ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int ifhwioctl (int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipoib_propagate_ifnet_mtu(struct ipoib_dev_priv *priv, int new_mtu,
    bool propagate)
{
	struct ifnet *ifp;
	struct ifreq ifr;
	int error;

	ifp = priv->dev;
	if (ifp->if_mtu == new_mtu)
		return (0);
	if (propagate) {
		strlcpy(ifr.ifr_name, if_name(ifp), IFNAMSIZ);
		ifr.ifr_mtu = new_mtu;
		CURVNET_SET(ifp->if_vnet);
		error = ifhwioctl(SIOCSIFMTU, ifp, (caddr_t)&ifr, curthread);
		CURVNET_RESTORE();
	} else {
		ifp->if_mtu = new_mtu;
		error = 0;
	}
	return (error);
}