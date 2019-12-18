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
struct ifnet {int if_flags; struct al_eth_adapter* if_softc; } ;
struct al_eth_adapter {int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  mii_mediachg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
al_media_update(struct ifnet *ifp)
{
	struct al_eth_adapter *adapter = ifp->if_softc;

	if ((ifp->if_flags & IFF_UP) != 0)
		mii_mediachg(adapter->mii);

	return (0);
}