#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct ifg_req* ifgru_groups; } ;
struct TYPE_8__ {TYPE_3__ ifgr_ifgru; } ;
struct TYPE_5__ {scalar_t__ ifgru_groups; } ;
struct TYPE_6__ {TYPE_1__ ifgr_ifgru; } ;
union ifgroupreq_union {TYPE_4__ ifgr; TYPE_2__ ifgr32; } ;
struct ifg_req {int dummy; } ;

/* Variables and functions */
 scalar_t__ SV_CURPROC_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_ILP32 ; 

__attribute__((used)) static struct ifg_req *
ifgr_groups_get(void *ifgrp)
{
	union ifgroupreq_union *ifgrup;

	ifgrup = ifgrp;
#ifdef COMPAT_FREEBSD32
	if (SV_CURPROC_FLAG(SV_ILP32))
		return ((struct ifg_req *)(uintptr_t)
		    ifgrup->ifgr32.ifgr_ifgru.ifgru_groups);
#endif
	return (ifgrup->ifgr.ifgr_ifgru.ifgru_groups);
}