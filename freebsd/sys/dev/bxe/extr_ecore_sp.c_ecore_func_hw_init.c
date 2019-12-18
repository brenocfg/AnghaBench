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
struct TYPE_3__ {int load_phase; } ;
struct TYPE_4__ {TYPE_1__ hw_init; } ;
struct ecore_func_state_params {struct ecore_func_sp_obj* f_obj; TYPE_2__ params; } ;
struct ecore_func_sp_obj {int /*<<< orphan*/  (* complete_cmd ) (struct bxe_softc*,struct ecore_func_sp_obj*,int /*<<< orphan*/ ) ;struct ecore_func_sp_drv_ops* drv; } ;
struct ecore_func_sp_drv_ops {int (* gunzip_init ) (struct bxe_softc*) ;int (* init_fw ) (struct bxe_softc*) ;int /*<<< orphan*/  (* gunzip_end ) (struct bxe_softc*) ;} ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ABS_FUNC_ID (struct bxe_softc*) ; 
 int /*<<< orphan*/  ECORE_ERR (char*,...) ; 
 int /*<<< orphan*/  ECORE_F_CMD_HW_INIT ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int /*<<< orphan*/ ,int) ; 
#define  FW_MSG_CODE_DRV_LOAD_COMMON 131 
#define  FW_MSG_CODE_DRV_LOAD_COMMON_CHIP 130 
#define  FW_MSG_CODE_DRV_LOAD_FUNCTION 129 
#define  FW_MSG_CODE_DRV_LOAD_PORT 128 
 int ecore_func_init_cmn (struct bxe_softc*,struct ecore_func_sp_drv_ops const*) ; 
 int ecore_func_init_cmn_chip (struct bxe_softc*,struct ecore_func_sp_drv_ops const*) ; 
 int ecore_func_init_func (struct bxe_softc*,struct ecore_func_sp_drv_ops const*) ; 
 int ecore_func_init_port (struct bxe_softc*,struct ecore_func_sp_drv_ops const*) ; 
 int stub1 (struct bxe_softc*) ; 
 int stub2 (struct bxe_softc*) ; 
 int /*<<< orphan*/  stub3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  stub4 (struct bxe_softc*,struct ecore_func_sp_obj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecore_func_hw_init(struct bxe_softc *sc,
			      struct ecore_func_state_params *params)
{
	uint32_t load_code = params->params.hw_init.load_phase;
	struct ecore_func_sp_obj *o = params->f_obj;
	const struct ecore_func_sp_drv_ops *drv = o->drv;
	int rc = 0;

	ECORE_MSG(sc, "function %d  load_code %x\n",
		  ECORE_ABS_FUNC_ID(sc), load_code);

	/* Prepare buffers for unzipping the FW */
	rc = drv->gunzip_init(sc);
	if (rc)
		return rc;

	/* Prepare FW */
	rc = drv->init_fw(sc);
	if (rc) {
		ECORE_ERR("Error loading firmware\n");
		goto init_err;
	}

	/* Handle the beginning of COMMON_XXX pases separately... */
	switch (load_code) {
	case FW_MSG_CODE_DRV_LOAD_COMMON_CHIP:
		rc = ecore_func_init_cmn_chip(sc, drv);
		if (rc)
			goto init_err;

		break;
	case FW_MSG_CODE_DRV_LOAD_COMMON:
		rc = ecore_func_init_cmn(sc, drv);
		if (rc)
			goto init_err;

		break;
	case FW_MSG_CODE_DRV_LOAD_PORT:
		rc = ecore_func_init_port(sc, drv);
		if (rc)
			goto init_err;

		break;
	case FW_MSG_CODE_DRV_LOAD_FUNCTION:
		rc = ecore_func_init_func(sc, drv);
		if (rc)
			goto init_err;

		break;
	default:
		ECORE_ERR("Unknown load_code (0x%x) from MCP\n", load_code);
		rc = ECORE_INVAL;
	}

init_err:
	drv->gunzip_end(sc);

	/* In case of success, complete the command immediately: no ramrods
	 * have been sent.
	 */
	if (!rc)
		o->complete_cmd(sc, o, ECORE_F_CMD_HW_INIT);

	return rc;
}