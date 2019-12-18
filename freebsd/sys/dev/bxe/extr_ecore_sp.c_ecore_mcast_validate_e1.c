#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ecore_mcast_ramrod_params {int mcast_list_len; struct ecore_mcast_obj* mcast_obj; } ;
struct ecore_mcast_obj {int (* get_registry_size ) (struct ecore_mcast_obj*) ;scalar_t__ max_cmd_len; int /*<<< orphan*/  total_pending_num; int /*<<< orphan*/  (* set_registry_size ) (struct ecore_mcast_obj*,scalar_t__) ;} ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_mcast_cmd { ____Placeholder_ecore_mcast_cmd } ecore_mcast_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ERR (char*,int) ; 
 int ECORE_INVAL ; 
#define  ECORE_MCAST_CMD_ADD 131 
#define  ECORE_MCAST_CMD_CONT 130 
#define  ECORE_MCAST_CMD_DEL 129 
#define  ECORE_MCAST_CMD_RESTORE 128 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,scalar_t__,...) ; 
 int ECORE_SUCCESS ; 
 int stub1 (struct ecore_mcast_obj*) ; 
 int /*<<< orphan*/  stub2 (struct ecore_mcast_obj*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct ecore_mcast_obj*,scalar_t__) ; 

__attribute__((used)) static int ecore_mcast_validate_e1(struct bxe_softc *sc,
				   struct ecore_mcast_ramrod_params *p,
				   enum ecore_mcast_cmd cmd)
{
	struct ecore_mcast_obj *o = p->mcast_obj;
	int reg_sz = o->get_registry_size(o);

	switch (cmd) {
	/* DEL command deletes all currently configured MACs */
	case ECORE_MCAST_CMD_DEL:
		o->set_registry_size(o, 0);
		/* Don't break */

	/* RESTORE command will restore the entire multicast configuration */
	case ECORE_MCAST_CMD_RESTORE:
		p->mcast_list_len = reg_sz;
		  ECORE_MSG(sc, "Command %d, p->mcast_list_len=%d\n",
				  cmd, p->mcast_list_len);
		break;

	case ECORE_MCAST_CMD_ADD:
	case ECORE_MCAST_CMD_CONT:
		/* Multicast MACs on 57710 are configured as unicast MACs and
		 * there is only a limited number of CAM entries for that
		 * matter.
		 */
		if (p->mcast_list_len > o->max_cmd_len) {
			ECORE_ERR("Can't configure more than %d multicast MACs on 57710\n",
				  o->max_cmd_len);
			return ECORE_INVAL;
		}
		/* Every configured MAC should be cleared if DEL command is
		 * called. Only the last ADD command is relevant as long as
		 * every ADD commands overrides the previous configuration.
		 */
		ECORE_MSG(sc, "p->mcast_list_len=%d\n", p->mcast_list_len);
		if (p->mcast_list_len > 0)
			o->set_registry_size(o, p->mcast_list_len);

		break;

	default:
		ECORE_ERR("Unknown command: %d\n", cmd);
		return ECORE_INVAL;
	}

	/* We want to ensure that commands are executed one by one for 57710.
	 * Therefore each none-empty command will consume o->max_cmd_len.
	 */
	if (p->mcast_list_len)
		o->total_pending_num += o->max_cmd_len;

	return ECORE_SUCCESS;
}