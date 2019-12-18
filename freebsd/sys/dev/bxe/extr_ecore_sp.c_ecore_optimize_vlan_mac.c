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
struct ecore_exe_queue_obj {int /*<<< orphan*/  exe_queue; struct ecore_exeq_elem* (* get ) (struct ecore_exe_queue_obj*,struct ecore_exeq_elem*) ;} ;
struct ecore_vlan_mac_obj {int /*<<< orphan*/  (* get_credit ) (struct ecore_vlan_mac_obj*) ;int /*<<< orphan*/  (* put_credit ) (struct ecore_vlan_mac_obj*) ;struct ecore_exe_queue_obj exe_queue; } ;
union ecore_qable_obj {struct ecore_vlan_mac_obj vlan_mac; } ;
struct TYPE_3__ {int cmd; int /*<<< orphan*/  vlan_mac_flags; } ;
struct TYPE_4__ {TYPE_1__ vlan_mac; } ;
struct ecore_exeq_elem {int /*<<< orphan*/  link; TYPE_2__ cmd_data; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  query ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_DONT_CONSUME_CAM_CREDIT ; 
 int /*<<< orphan*/  ECORE_ERR (char*) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_LIST_REMOVE_ENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECORE_MEMCPY (struct ecore_exeq_elem*,struct ecore_exeq_elem*,int) ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,char*) ; 
 int /*<<< orphan*/  ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  ECORE_VLAN_MAC_ADD 129 
#define  ECORE_VLAN_MAC_DEL 128 
 int /*<<< orphan*/  ecore_exe_queue_free_elem (struct bxe_softc*,struct ecore_exeq_elem*) ; 
 struct ecore_exeq_elem* stub1 (struct ecore_exe_queue_obj*,struct ecore_exeq_elem*) ; 
 int /*<<< orphan*/  stub2 (struct ecore_vlan_mac_obj*) ; 
 int /*<<< orphan*/  stub3 (struct ecore_vlan_mac_obj*) ; 

__attribute__((used)) static int ecore_optimize_vlan_mac(struct bxe_softc *sc,
				   union ecore_qable_obj *qo,
				   struct ecore_exeq_elem *elem)
{
	struct ecore_exeq_elem query, *pos;
	struct ecore_vlan_mac_obj *o = &qo->vlan_mac;
	struct ecore_exe_queue_obj *exeq = &o->exe_queue;

	ECORE_MEMCPY(&query, elem, sizeof(query));

	switch (elem->cmd_data.vlan_mac.cmd) {
	case ECORE_VLAN_MAC_ADD:
		query.cmd_data.vlan_mac.cmd = ECORE_VLAN_MAC_DEL;
		break;
	case ECORE_VLAN_MAC_DEL:
		query.cmd_data.vlan_mac.cmd = ECORE_VLAN_MAC_ADD;
		break;
	default:
		/* Don't handle anything other than ADD or DEL */
		return 0;
	}

	/* If we found the appropriate element - delete it */
	pos = exeq->get(exeq, &query);
	if (pos) {

		/* Return the credit of the optimized command */
		if (!ECORE_TEST_BIT(ECORE_DONT_CONSUME_CAM_CREDIT,
				     &pos->cmd_data.vlan_mac.vlan_mac_flags)) {
			if ((query.cmd_data.vlan_mac.cmd ==
			     ECORE_VLAN_MAC_ADD) && !o->put_credit(o)) {
				ECORE_ERR("Failed to return the credit for the optimized ADD command\n");
				return ECORE_INVAL;
			} else if (!o->get_credit(o)) { /* VLAN_MAC_DEL */
				ECORE_ERR("Failed to recover the credit from the optimized DEL command\n");
				return ECORE_INVAL;
			}
		}

		ECORE_MSG(sc, "Optimizing %s command\n",
			  (elem->cmd_data.vlan_mac.cmd == ECORE_VLAN_MAC_ADD) ?
			  "ADD" : "DEL");

		ECORE_LIST_REMOVE_ENTRY(&pos->link, &exeq->exe_queue);
		ecore_exe_queue_free_elem(sc, pos);
		return 1;
	}

	return 0;
}