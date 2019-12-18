#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* if_shared_ctx_t ;
typedef  TYPE_2__* if_pseudo_t ;
struct TYPE_9__ {int /*<<< orphan*/ * ip_ifc; int /*<<< orphan*/ * ip_lladdr_tag; int /*<<< orphan*/ * ip_detach_tag; int /*<<< orphan*/ * ip_dc; TYPE_1__* ip_sctx; } ;
struct TYPE_8__ {char* isc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFC_NOGROUP ; 
 int /*<<< orphan*/  M_IFLIB ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * devclass_create (char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_clone_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * if_clone_simple (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifc_flags_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_clone_create ; 
 int /*<<< orphan*/  iflib_clone_destroy ; 
 int /*<<< orphan*/  iflib_ifdetach ; 
 int /*<<< orphan*/  iflib_iflladdr ; 
 int /*<<< orphan*/  iflib_ip_insert (TYPE_2__*) ; 
 int /*<<< orphan*/ * iflib_ip_lookup (char*) ; 
 int /*<<< orphan*/  iflladdr_event ; 
 int /*<<< orphan*/  ifnet_departure_event ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

if_pseudo_t
iflib_clone_register(if_shared_ctx_t sctx)
{
	if_pseudo_t ip;

	if (sctx->isc_name == NULL) {
		printf("iflib_clone_register failed - shared_ctx needs to have a device name\n");
		return (NULL);
	}
	if (iflib_ip_lookup(sctx->isc_name) != NULL) {
		printf("iflib_clone_register failed - shared_ctx %s alread registered\n",
			   sctx->isc_name);
		return (NULL);
	}
	ip = malloc(sizeof(*ip), M_IFLIB, M_WAITOK|M_ZERO);
	ip->ip_sctx = sctx;
	ip->ip_dc = devclass_create(sctx->isc_name);
	if (ip->ip_dc == NULL)
		goto fail_clone;
	/* XXX --- we can handle clone_advanced later */
	ip->ip_ifc  = if_clone_simple(sctx->isc_name, iflib_clone_create, iflib_clone_destroy, 0);
	if (ip->ip_ifc == NULL) {
		printf("clone_simple failed -- cloned %s  devices will not be available\n", sctx->isc_name);
		goto fail_clone;
	}
	ifc_flags_set(ip->ip_ifc, IFC_NOGROUP);
	ip->ip_lladdr_tag = EVENTHANDLER_REGISTER(iflladdr_event,
											 iflib_iflladdr, NULL, EVENTHANDLER_PRI_ANY);
	if (ip->ip_lladdr_tag == NULL)
		goto fail_addr;
	ip->ip_detach_tag = EVENTHANDLER_REGISTER(ifnet_departure_event,
											 iflib_ifdetach, NULL, EVENTHANDLER_PRI_ANY);

	if (ip->ip_detach_tag == NULL)
		goto fail_depart;

	iflib_ip_insert(ip);
	return (ip);
 fail_depart:
	EVENTHANDLER_DEREGISTER(iflladdr_event, ip->ip_lladdr_tag);
 fail_addr:
	if_clone_detach(ip->ip_ifc);
 fail_clone:
	free(ip, M_IFLIB);
	return (NULL);
}