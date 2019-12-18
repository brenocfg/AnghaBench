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
typedef  int rpcproc_t ;

/* Variables and functions */
 int NFSV2PROC_STATFS ; 
 int* newnfs_nfsv3_procid ; 

rpcproc_t
fhanew_get_procnum(rpcproc_t procnum)
{
	if (procnum > NFSV2PROC_STATFS)
		return (-1);

	return (newnfs_nfsv3_procid[procnum]);
}