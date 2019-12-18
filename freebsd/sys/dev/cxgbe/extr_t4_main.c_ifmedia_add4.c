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
struct ifmedia {int dummy; } ;

/* Variables and functions */
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 
 int /*<<< orphan*/  ifmedia_add (struct ifmedia*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ifmedia_add4(struct ifmedia *ifm, int m)
{

	ifmedia_add(ifm, m, 0, NULL);
	ifmedia_add(ifm, m | IFM_ETH_TXPAUSE, 0, NULL);
	ifmedia_add(ifm, m | IFM_ETH_RXPAUSE, 0, NULL);
	ifmedia_add(ifm, m | IFM_ETH_TXPAUSE | IFM_ETH_RXPAUSE, 0, NULL);
}