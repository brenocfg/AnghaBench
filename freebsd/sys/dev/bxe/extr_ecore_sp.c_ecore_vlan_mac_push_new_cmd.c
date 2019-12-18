#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cmd; } ;
struct ecore_vlan_mac_ramrod_params {TYPE_2__ user_req; int /*<<< orphan*/  ramrod_flags; struct ecore_vlan_mac_obj* vlan_mac_obj; } ;
struct ecore_vlan_mac_obj {int /*<<< orphan*/  exe_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  vlan_mac; } ;
struct ecore_exeq_elem {int cmd_len; TYPE_1__ cmd_data; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MEMCPY (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int ECORE_NOMEM ; 
 int ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  ECORE_VLAN_MAC_MOVE 128 
 int /*<<< orphan*/  RAMROD_RESTORE ; 
 int ecore_exe_queue_add (struct bxe_softc*,int /*<<< orphan*/ *,struct ecore_exeq_elem*,int) ; 
 struct ecore_exeq_elem* ecore_exe_queue_alloc_elem (struct bxe_softc*) ; 

__attribute__((used)) static inline int ecore_vlan_mac_push_new_cmd(
	struct bxe_softc *sc,
	struct ecore_vlan_mac_ramrod_params *p)
{
	struct ecore_exeq_elem *elem;
	struct ecore_vlan_mac_obj *o = p->vlan_mac_obj;
	bool restore = ECORE_TEST_BIT(RAMROD_RESTORE, &p->ramrod_flags);

	/* Allocate the execution queue element */
	elem = ecore_exe_queue_alloc_elem(sc);
	if (!elem)
		return ECORE_NOMEM;

	/* Set the command 'length' */
	switch (p->user_req.cmd) {
	case ECORE_VLAN_MAC_MOVE:
		elem->cmd_len = 2;
		break;
	default:
		elem->cmd_len = 1;
	}

	/* Fill the object specific info */
	ECORE_MEMCPY(&elem->cmd_data.vlan_mac, &p->user_req, sizeof(p->user_req));

	/* Try to add a new command to the pending list */
	return ecore_exe_queue_add(sc, &o->exe_queue, elem, restore);
}