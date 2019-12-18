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
struct lio {int /*<<< orphan*/  oct_dev; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSUM_IP_TSO ; 
 int EINVAL ; 
 int IFCAP_TSO4 ; 
 int if_getcapabilities (struct ifnet*) ; 
 int if_getcapenable (struct ifnet*) ; 
 struct lio* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  if_sethwassistbits (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_togglecapenable (struct ifnet*,int) ; 
 int /*<<< orphan*/  lio_dev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
lio_set_tso4(struct ifnet *ifp)
{
	struct lio	*lio = if_getsoftc(ifp);

	if (if_getcapabilities(ifp) & IFCAP_TSO4) {
		if_togglecapenable(ifp, IFCAP_TSO4);
		if (if_getcapenable(ifp) & IFCAP_TSO4)
			if_sethwassistbits(ifp, CSUM_IP_TSO, 0);
		else
			if_sethwassistbits(ifp, 0, CSUM_IP_TSO);
	} else {
		lio_dev_info(lio->oct_dev, "TSO4 capability not supported\n");
		return (EINVAL);
	}

	return (0);
}