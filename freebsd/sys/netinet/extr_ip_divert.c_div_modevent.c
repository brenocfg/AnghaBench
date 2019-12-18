#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_4__ {int /*<<< orphan*/  ipi_count; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_INFO_WLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  INP_INFO_WUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  IPPROTO_DIVERT ; 
#define  MOD_LOAD 130 
#define  MOD_QUIESCE 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 TYPE_1__ V_divcbinfo ; 
 int /*<<< orphan*/  div_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  div_protosw ; 
 int /*<<< orphan*/  div_zone_change ; 
 int /*<<< orphan*/ * divert_packet ; 
 int /*<<< orphan*/  ip_divert_event_tag ; 
 int /*<<< orphan*/ * ip_divert_ptr ; 
 int /*<<< orphan*/  maxsockets_change ; 
 int pf_proto_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pf_proto_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
div_modevent(module_t mod, int type, void *unused)
{
	int err = 0;

	switch (type) {
	case MOD_LOAD:
		/*
		 * Protocol will be initialized by pf_proto_register().
		 * We don't have to register ip_protox because we are not
		 * a true IP protocol that goes over the wire.
		 */
		err = pf_proto_register(PF_INET, &div_protosw);
		if (err != 0)
			return (err);
		ip_divert_ptr = divert_packet;
		ip_divert_event_tag = EVENTHANDLER_REGISTER(maxsockets_change,
		    div_zone_change, NULL, EVENTHANDLER_PRI_ANY);
		break;
	case MOD_QUIESCE:
		/*
		 * IPDIVERT may normally not be unloaded because of the
		 * potential race conditions.  Tell kldunload we can't be
		 * unloaded unless the unload is forced.
		 */
		err = EPERM;
		break;
	case MOD_UNLOAD:
		/*
		 * Forced unload.
		 *
		 * Module ipdivert can only be unloaded if no sockets are
		 * connected.  Maybe this can be changed later to forcefully
		 * disconnect any open sockets.
		 *
		 * XXXRW: Note that there is a slight race here, as a new
		 * socket open request could be spinning on the lock and then
		 * we destroy the lock.
		 */
		INP_INFO_WLOCK(&V_divcbinfo);
		if (V_divcbinfo.ipi_count != 0) {
			err = EBUSY;
			INP_INFO_WUNLOCK(&V_divcbinfo);
			break;
		}
		ip_divert_ptr = NULL;
		err = pf_proto_unregister(PF_INET, IPPROTO_DIVERT, SOCK_RAW);
		INP_INFO_WUNLOCK(&V_divcbinfo);
#ifndef VIMAGE
		div_destroy(NULL);
#endif
		EVENTHANDLER_DEREGISTER(maxsockets_change, ip_divert_event_tag);
		break;
	default:
		err = EOPNOTSUPP;
		break;
	}
	return err;
}