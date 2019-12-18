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
typedef  int uint32_t ;
struct TYPE_3__ {int reset_phase; } ;
struct TYPE_4__ {TYPE_1__ hw_reset; } ;
struct ecore_func_state_params {struct ecore_func_sp_obj* f_obj; TYPE_2__ params; } ;
struct ecore_func_sp_obj {int /*<<< orphan*/  (* complete_cmd ) (struct bxe_softc*,struct ecore_func_sp_obj*,int /*<<< orphan*/ ) ;struct ecore_func_sp_drv_ops* drv; } ;
struct ecore_func_sp_drv_ops {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ABS_FUNC_ID (struct bxe_softc*) ; 
 int /*<<< orphan*/  ECORE_ERR (char*,int) ; 
 int /*<<< orphan*/  ECORE_F_CMD_HW_RESET ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int /*<<< orphan*/ ,int) ; 
 int ECORE_SUCCESS ; 
#define  FW_MSG_CODE_DRV_UNLOAD_COMMON 130 
#define  FW_MSG_CODE_DRV_UNLOAD_FUNCTION 129 
#define  FW_MSG_CODE_DRV_UNLOAD_PORT 128 
 int /*<<< orphan*/  ecore_func_reset_cmn (struct bxe_softc*,struct ecore_func_sp_drv_ops const*) ; 
 int /*<<< orphan*/  ecore_func_reset_func (struct bxe_softc*,struct ecore_func_sp_drv_ops const*) ; 
 int /*<<< orphan*/  ecore_func_reset_port (struct bxe_softc*,struct ecore_func_sp_drv_ops const*) ; 
 int /*<<< orphan*/  stub1 (struct bxe_softc*,struct ecore_func_sp_obj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ecore_func_hw_reset(struct bxe_softc *sc,
				      struct ecore_func_state_params *params)
{
	uint32_t reset_phase = params->params.hw_reset.reset_phase;
	struct ecore_func_sp_obj *o = params->f_obj;
	const struct ecore_func_sp_drv_ops *drv = o->drv;

	ECORE_MSG(sc, "function %d  reset_phase %x\n", ECORE_ABS_FUNC_ID(sc),
		  reset_phase);

	switch (reset_phase) {
	case FW_MSG_CODE_DRV_UNLOAD_COMMON:
		ecore_func_reset_cmn(sc, drv);
		break;
	case FW_MSG_CODE_DRV_UNLOAD_PORT:
		ecore_func_reset_port(sc, drv);
		break;
	case FW_MSG_CODE_DRV_UNLOAD_FUNCTION:
		ecore_func_reset_func(sc, drv);
		break;
	default:
		ECORE_ERR("Unknown reset_phase (0x%x) from MCP\n",
			  reset_phase);
		break;
	}

	/* Complete the command immediately: no ramrods have been sent. */
	o->complete_cmd(sc, o, ECORE_F_CMD_HW_RESET);

	return ECORE_SUCCESS;
}