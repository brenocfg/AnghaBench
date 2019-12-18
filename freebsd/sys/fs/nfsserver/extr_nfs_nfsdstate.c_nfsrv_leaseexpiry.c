#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ nsf_eograce; } ;

/* Variables and functions */
 scalar_t__ NFSD_MONOSEC ; 
 int NFSRV_LEASEDELTA ; 
 int nfsrv_lease ; 
 TYPE_1__ nfsrv_stablefirst ; 

__attribute__((used)) static time_t
nfsrv_leaseexpiry(void)
{

	if (nfsrv_stablefirst.nsf_eograce > NFSD_MONOSEC)
		return (NFSD_MONOSEC + 2 * (nfsrv_lease + NFSRV_LEASEDELTA));
	return (NFSD_MONOSEC + nfsrv_lease + NFSRV_LEASEDELTA);
}