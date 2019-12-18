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
struct ifnet {scalar_t__ if_type; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ IFT_LOOP ; 
 scalar_t__ ifoff_bpfrecv_enabled ; 
 int /*<<< orphan*/  ifoff_enabled ; 
 scalar_t__ ifoff_lo_enabled ; 
 scalar_t__ ifoff_other_enabled ; 

__attribute__((used)) static int
ifnet_check_incoming(struct ifnet *ifp, int viabpf)
{
	if (!ifoff_enabled)
		return (0);

	if (ifoff_lo_enabled && ifp->if_type == IFT_LOOP)
		return (0);

	if (ifoff_other_enabled && ifp->if_type != IFT_LOOP)
		return (0);

	if (viabpf && ifoff_bpfrecv_enabled)
		return (0);

	return (EPERM);
}