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
struct ecore_vlan_mac_registry_elem {int /*<<< orphan*/  vlan_mac_flags; int /*<<< orphan*/  u; int /*<<< orphan*/  cam_offset; } ;
struct ecore_vlan_mac_obj {struct ecore_vlan_mac_registry_elem* (* check_del ) (struct bxe_softc*,struct ecore_vlan_mac_obj*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_cam_offset ) (struct ecore_vlan_mac_obj*,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int cmd; int /*<<< orphan*/  u; int /*<<< orphan*/  vlan_mac_flags; } ;
struct TYPE_4__ {TYPE_1__ vlan_mac; } ;
struct ecore_exeq_elem {TYPE_2__ cmd_data; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_vlan_mac_cmd { ____Placeholder_ecore_vlan_mac_cmd } ecore_vlan_mac_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_DBG_BREAK_IF (int) ; 
 int /*<<< orphan*/  ECORE_FREE (struct bxe_softc*,struct ecore_vlan_mac_registry_elem*,int) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int /*<<< orphan*/ ) ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int ECORE_VLAN_MAC_ADD ; 
 int ECORE_VLAN_MAC_MOVE ; 
 struct ecore_vlan_mac_registry_elem* ECORE_ZALLOC (int,int /*<<< orphan*/ ,struct bxe_softc*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  stub1 (struct ecore_vlan_mac_obj*,int /*<<< orphan*/ *) ; 
 struct ecore_vlan_mac_registry_elem* stub2 (struct bxe_softc*,struct ecore_vlan_mac_obj*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ecore_vlan_mac_get_registry_elem(
	struct bxe_softc *sc,
	struct ecore_vlan_mac_obj *o,
	struct ecore_exeq_elem *elem,
	bool restore,
	struct ecore_vlan_mac_registry_elem **re)
{
	enum ecore_vlan_mac_cmd cmd = elem->cmd_data.vlan_mac.cmd;
	struct ecore_vlan_mac_registry_elem *reg_elem;

	/* Allocate a new registry element if needed. */
	if (!restore &&
	    ((cmd == ECORE_VLAN_MAC_ADD) || (cmd == ECORE_VLAN_MAC_MOVE))) {
		reg_elem = ECORE_ZALLOC(sizeof(*reg_elem), GFP_ATOMIC, sc);
		if (!reg_elem)
			return ECORE_NOMEM;

		/* Get a new CAM offset */
		if (!o->get_cam_offset(o, &reg_elem->cam_offset)) {
			/* This shall never happen, because we have checked the
			 * CAM availability in the 'validate'.
			 */
			ECORE_DBG_BREAK_IF(1);
			ECORE_FREE(sc, reg_elem, sizeof(*reg_elem));
			return ECORE_INVAL;
		}

		ECORE_MSG(sc, "Got cam offset %d\n", reg_elem->cam_offset);

		/* Set a VLAN-MAC data */
		ECORE_MEMCPY(&reg_elem->u, &elem->cmd_data.vlan_mac.u,
			  sizeof(reg_elem->u));

		/* Copy the flags (needed for DEL and RESTORE flows) */
		reg_elem->vlan_mac_flags =
			elem->cmd_data.vlan_mac.vlan_mac_flags;
	} else /* DEL, RESTORE */
		reg_elem = o->check_del(sc, o, &elem->cmd_data.vlan_mac.u);

	*re = reg_elem;
	return ECORE_SUCCESS;
}