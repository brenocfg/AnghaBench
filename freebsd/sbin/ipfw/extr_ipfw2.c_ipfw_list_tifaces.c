#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int count; scalar_t__ objsize; } ;
typedef  TYPE_1__ ipfw_obj_lheader ;
struct TYPE_7__ {int flags; char* ifname; int ifindex; int refcnt; int gencnt; } ;
typedef  TYPE_2__ ipfw_iface_info ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int IPFW_IFFLAG_RESOLVED ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ifinfo_cmp ; 
 int ipfw_get_tracked_ifaces (TYPE_1__**) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,...) ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipfw_list_tifaces()
{
	ipfw_obj_lheader *olh;
	ipfw_iface_info *info;
	int i, error;

	if ((error = ipfw_get_tracked_ifaces(&olh)) != 0)
		err(EX_OSERR, "Unable to request ipfw tracked interface list");


	qsort(olh + 1, olh->count, olh->objsize, ifinfo_cmp);

	info = (ipfw_iface_info *)(olh + 1);
	for (i = 0; i < olh->count; i++) {
		if (info->flags & IPFW_IFFLAG_RESOLVED)
			printf("%s ifindex: %d refcount: %u changes: %u\n",
			    info->ifname, info->ifindex, info->refcnt,
			    info->gencnt);
		else
			printf("%s ifindex: unresolved refcount: %u changes: %u\n",
			    info->ifname, info->refcnt, info->gencnt);
		info = (ipfw_iface_info *)((caddr_t)info + olh->objsize);
	}

	free(olh);
}