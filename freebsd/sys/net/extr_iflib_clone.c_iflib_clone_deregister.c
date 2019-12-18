#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* if_pseudo_t ;
struct TYPE_5__ {int /*<<< orphan*/  ip_ifc; int /*<<< orphan*/  ip_lladdr_tag; int /*<<< orphan*/  ip_detach_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IFLIB ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_clone_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_ip_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  iflladdr_event ; 
 int /*<<< orphan*/  ifnet_departure_event ; 

void
iflib_clone_deregister(if_pseudo_t ip)
{
	/* XXX check that is not still in use */
	iflib_ip_delete(ip);
	EVENTHANDLER_DEREGISTER(ifnet_departure_event, ip->ip_detach_tag);
	EVENTHANDLER_DEREGISTER(iflladdr_event, ip->ip_lladdr_tag);
	if_clone_detach(ip->ip_ifc);
	/* XXX free devclass */
	free(ip, M_IFLIB);
}