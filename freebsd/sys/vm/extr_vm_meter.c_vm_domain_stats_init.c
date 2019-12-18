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
struct vm_domain {char* vmd_name; int /*<<< orphan*/  vmd_free_severe; int /*<<< orphan*/  vmd_free_min; int /*<<< orphan*/  vmd_free_reserved; int /*<<< orphan*/  vmd_free_target; int /*<<< orphan*/  vmd_inactive_target; TYPE_1__* vmd_pagequeues; int /*<<< orphan*/  vmd_free_count; struct sysctl_oid* vmd_oid; } ;
struct sysctl_oid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pq_pdpages; int /*<<< orphan*/  pq_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 size_t PQ_ACTIVE ; 
 size_t PQ_INACTIVE ; 
 size_t PQ_LAUNDRY ; 
 size_t PQ_UNSWAPPABLE ; 
 void* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 

__attribute__((used)) static void
vm_domain_stats_init(struct vm_domain *vmd, struct sysctl_oid *parent)
{
	struct sysctl_oid *oid;

	vmd->vmd_oid = SYSCTL_ADD_NODE(NULL, SYSCTL_CHILDREN(parent), OID_AUTO,
	    vmd->vmd_name, CTLFLAG_RD, NULL, "");
	oid = SYSCTL_ADD_NODE(NULL, SYSCTL_CHILDREN(vmd->vmd_oid), OID_AUTO,
	    "stats", CTLFLAG_RD, NULL, "");
	SYSCTL_ADD_UINT(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "free_count", CTLFLAG_RD, &vmd->vmd_free_count, 0,
	    "Free pages");
	SYSCTL_ADD_UINT(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "active", CTLFLAG_RD, &vmd->vmd_pagequeues[PQ_ACTIVE].pq_cnt, 0,
	    "Active pages");
	SYSCTL_ADD_U64(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "actpdpgs", CTLFLAG_RD,
	    &vmd->vmd_pagequeues[PQ_ACTIVE].pq_pdpages, 0,
	    "Active pages scanned by the page daemon");
	SYSCTL_ADD_UINT(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "inactive", CTLFLAG_RD, &vmd->vmd_pagequeues[PQ_INACTIVE].pq_cnt, 0,
	    "Inactive pages");
	SYSCTL_ADD_U64(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "inactpdpgs", CTLFLAG_RD,
	    &vmd->vmd_pagequeues[PQ_INACTIVE].pq_pdpages, 0,
	    "Inactive pages scanned by the page daemon");
	SYSCTL_ADD_UINT(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "laundry", CTLFLAG_RD, &vmd->vmd_pagequeues[PQ_LAUNDRY].pq_cnt, 0,
	    "laundry pages");
	SYSCTL_ADD_U64(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "laundpdpgs", CTLFLAG_RD,
	    &vmd->vmd_pagequeues[PQ_LAUNDRY].pq_pdpages, 0,
	    "Laundry pages scanned by the page daemon");
	SYSCTL_ADD_UINT(NULL, SYSCTL_CHILDREN(oid), OID_AUTO, "unswappable",
	    CTLFLAG_RD, &vmd->vmd_pagequeues[PQ_UNSWAPPABLE].pq_cnt, 0,
	    "Unswappable pages");
	SYSCTL_ADD_U64(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "unswppdpgs", CTLFLAG_RD,
	    &vmd->vmd_pagequeues[PQ_UNSWAPPABLE].pq_pdpages, 0,
	    "Unswappable pages scanned by the page daemon");
	SYSCTL_ADD_UINT(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "inactive_target", CTLFLAG_RD, &vmd->vmd_inactive_target, 0,
	    "Target inactive pages");
	SYSCTL_ADD_UINT(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "free_target", CTLFLAG_RD, &vmd->vmd_free_target, 0,
	    "Target free pages");
	SYSCTL_ADD_UINT(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "free_reserved", CTLFLAG_RD, &vmd->vmd_free_reserved, 0,
	    "Reserved free pages");
	SYSCTL_ADD_UINT(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "free_min", CTLFLAG_RD, &vmd->vmd_free_min, 0,
	    "Minimum free pages");
	SYSCTL_ADD_UINT(NULL, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "free_severe", CTLFLAG_RD, &vmd->vmd_free_severe, 0,
	    "Severe free pages");

}