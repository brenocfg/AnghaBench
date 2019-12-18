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
typedef  int /*<<< orphan*/  uint16_t ;
struct ifnet {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET_QUIET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TD_TO_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  if_rele (struct ifnet*) ; 
 struct ifnet* ifunit_ref (char*) ; 

__attribute__((used)) static uint16_t
krping_get_ipv6_scope_id(char *name)
{
	struct ifnet *ifp;
	uint16_t retval;

	if (name == NULL)
		return (0);
	CURVNET_SET_QUIET(TD_TO_VNET(curthread));
	ifp = ifunit_ref(name);
	CURVNET_RESTORE();
	if (ifp == NULL)
		return (0);
	retval = ifp->if_index;
	if_rele(ifp);
	return (retval);
}