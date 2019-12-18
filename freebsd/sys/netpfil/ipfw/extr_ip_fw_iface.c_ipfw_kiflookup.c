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
struct ifnet {int if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  if_rele (struct ifnet*) ; 
 struct ifnet* ifunit_ref (char*) ; 

__attribute__((used)) static int
ipfw_kiflookup(char *name)
{
	struct ifnet *ifp;
	int ifindex;

	ifindex = 0;

	if ((ifp = ifunit_ref(name)) != NULL) {
		ifindex = ifp->if_index;
		if_rele(ifp);
	}

	return (ifindex);
}