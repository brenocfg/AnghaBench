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
struct netmap_adapter {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  if_rele (struct ifnet*) ; 
 int /*<<< orphan*/  netmap_adapter_put (struct netmap_adapter*) ; 

void
netmap_unget_na(struct netmap_adapter *na, struct ifnet *ifp)
{
	if (ifp)
		if_rele(ifp);
	if (na)
		netmap_adapter_put(na);
}