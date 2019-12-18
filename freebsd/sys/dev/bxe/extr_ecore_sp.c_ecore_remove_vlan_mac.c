#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* put_credit ) (TYPE_3__*) ;int (* get_credit ) (TYPE_3__*) ;} ;
union ecore_qable_obj {TYPE_3__ vlan_mac; } ;
struct TYPE_5__ {int cmd; int /*<<< orphan*/  vlan_mac_flags; } ;
struct TYPE_6__ {TYPE_1__ vlan_mac; } ;
struct ecore_exeq_elem {TYPE_2__ cmd_data; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_DONT_CONSUME_CAM_CREDIT ; 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  ECORE_VLAN_MAC_ADD 130 
#define  ECORE_VLAN_MAC_DEL 129 
#define  ECORE_VLAN_MAC_MOVE 128 
 int TRUE ; 
 int stub1 (TYPE_3__*) ; 
 int stub2 (TYPE_3__*) ; 

__attribute__((used)) static int ecore_remove_vlan_mac(struct bxe_softc *sc,
				  union ecore_qable_obj *qo,
				  struct ecore_exeq_elem *elem)
{
	int rc = 0;

	/* If consumption wasn't required, nothing to do */
	if (ECORE_TEST_BIT(ECORE_DONT_CONSUME_CAM_CREDIT,
			   &elem->cmd_data.vlan_mac.vlan_mac_flags))
		return ECORE_SUCCESS;

	switch (elem->cmd_data.vlan_mac.cmd) {
	case ECORE_VLAN_MAC_ADD:
	case ECORE_VLAN_MAC_MOVE:
		rc = qo->vlan_mac.put_credit(&qo->vlan_mac);
		break;
	case ECORE_VLAN_MAC_DEL:
		rc = qo->vlan_mac.get_credit(&qo->vlan_mac);
		break;
	default:
		return ECORE_INVAL;
	}

	if (rc != TRUE)
		return ECORE_INVAL;

	return ECORE_SUCCESS;
}