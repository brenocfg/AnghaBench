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
struct ecore_mcast_obj {int (* get_registry_size ) (struct ecore_mcast_obj*) ;int /*<<< orphan*/  total_pending_num; int /*<<< orphan*/  (* set_registry_size ) (struct ecore_mcast_obj*,int) ;} ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_mcast_cmd { ____Placeholder_ecore_mcast_cmd } ecore_mcast_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ERR (char*,int) ; 
 int ECORE_INVAL ; 
#define  ECORE_MCAST_CMD_ADD 131 
#define  ECORE_MCAST_CMD_CONT 130 
#define  ECORE_MCAST_CMD_DEL 129 
#define  ECORE_MCAST_CMD_RESTORE 128 
 int ECORE_SUCCESS ; 
 int stub1 (struct ecore_mcast_obj*) ; 
 int /*<<< orphan*/  stub2 (struct ecore_mcast_obj*,int) ; 
 int /*<<< orphan*/  stub3 (struct ecore_mcast_obj*,int) ; 

__attribute__((used)) static int ecore_mcast_validate_e2(struct bxe_softc *sc,
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
		/* Here we set the approximate amount of work to do, which in
		 * fact may be only less as some MACs in postponed ADD
		 * command(s) scheduled before this command may fall into
		 * the same bin and the actual number of bins set in the
		 * registry would be less than we estimated here. See
		 * ecore_mcast_set_one_rule_e2() for further details.
		 */
		p->mcast_list_len = reg_sz;
		break;

	case ECORE_MCAST_CMD_ADD:
	case ECORE_MCAST_CMD_CONT:
		/* Here we assume that all new MACs will fall into new bins.
		 * However we will correct the real registry size after we
		 * handle all pending commands.
		 */
		o->set_registry_size(o, reg_sz + p->mcast_list_len);
		break;

	default:
		ECORE_ERR("Unknown command: %d\n", cmd);
		return ECORE_INVAL;
	}

	/* Increase the total number of MACs pending to be configured */
	o->total_pending_num += p->mcast_list_len;

	return ECORE_SUCCESS;
}