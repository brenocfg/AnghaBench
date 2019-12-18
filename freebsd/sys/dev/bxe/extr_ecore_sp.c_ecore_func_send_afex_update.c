#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct function_update_data {int vif_id_change_flg; int afex_default_vlan_change_flg; int allowed_priorities_change_flg; int /*<<< orphan*/  allowed_priorities; void* afex_default_vlan; void* vif_id; int /*<<< orphan*/  echo; } ;
struct ecore_func_afex_update_params {int /*<<< orphan*/  allowed_priorities; int /*<<< orphan*/  afex_default_vlan; int /*<<< orphan*/  vif_id; } ;
struct TYPE_2__ {struct ecore_func_afex_update_params afex_update; } ;
struct ecore_func_state_params {TYPE_1__ params; struct ecore_func_sp_obj* f_obj; } ;
struct ecore_func_sp_obj {int /*<<< orphan*/  afex_rdata_mapping; scalar_t__ afex_rdata; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFEX_UPDATE ; 
 void* ECORE_CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MEMSET (struct function_update_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NONE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_COMMON_FUNCTION_UPDATE ; 
 int ecore_sp_post (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ecore_func_send_afex_update(struct bxe_softc *sc,
					 struct ecore_func_state_params *params)
{
	struct ecore_func_sp_obj *o = params->f_obj;
	struct function_update_data *rdata =
		(struct function_update_data *)o->afex_rdata;
	ecore_dma_addr_t data_mapping = o->afex_rdata_mapping;
	struct ecore_func_afex_update_params *afex_update_params =
		&params->params.afex_update;

	ECORE_MEMSET(rdata, 0, sizeof(*rdata));

	/* Fill the ramrod data with provided parameters */
	rdata->vif_id_change_flg = 1;
	rdata->vif_id = ECORE_CPU_TO_LE16(afex_update_params->vif_id);
	rdata->afex_default_vlan_change_flg = 1;
	rdata->afex_default_vlan =
		ECORE_CPU_TO_LE16(afex_update_params->afex_default_vlan);
	rdata->allowed_priorities_change_flg = 1;
	rdata->allowed_priorities = afex_update_params->allowed_priorities;
	rdata->echo = AFEX_UPDATE;

	/* No need for an explicit memory barrier here as long as we
	 * ensure the ordering of writing to the SPQ element
	 *  and updating of the SPQ producer which involves a memory
	 * read. If the memory read is removed we will have to put a
	 * full memory barrier there (inside ecore_sp_post()).
	 */
	ECORE_MSG(sc,
		  "afex: sending func_update vif_id 0x%x dvlan 0x%x prio 0x%x\n",
		  rdata->vif_id,
		  rdata->afex_default_vlan, rdata->allowed_priorities);

	return ecore_sp_post(sc, RAMROD_CMD_ID_COMMON_FUNCTION_UPDATE, 0,
			     data_mapping, NONE_CONNECTION_TYPE);
}