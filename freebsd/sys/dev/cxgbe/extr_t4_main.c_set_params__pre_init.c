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
typedef  int uint32_t ;
struct TYPE_2__ {int fw_vers; int viid_smt_extn_support; } ;
struct adapter {TYPE_1__ params; int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_T6 ; 
 int FW_EINVAL ; 
 int FW_PARAM_DEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPFILTER_REGION_SUPPORT ; 
 int /*<<< orphan*/  OPAQUE_VIID_SMT_EXTN ; 
 int V_FW_HDR_FW_VER_BUILD (int /*<<< orphan*/ ) ; 
 int V_FW_HDR_FW_VER_MAJOR (int) ; 
 int V_FW_HDR_FW_VER_MICRO (int) ; 
 int V_FW_HDR_FW_VER_MINOR (int) ; 
 scalar_t__ chip_id (struct adapter*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int t4_set_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 

__attribute__((used)) static int
set_params__pre_init(struct adapter *sc)
{
	int rc = 0;
	uint32_t param, val;

	if (chip_id(sc) >= CHELSIO_T6) {
		param = FW_PARAM_DEV(HPFILTER_REGION_SUPPORT);
		val = 1;
		rc = -t4_set_params(sc, sc->mbox, sc->pf, 0, 1, &param, &val);
		/* firmwares < 1.20.1.0 do not have this param. */
		if (rc == FW_EINVAL && sc->params.fw_vers <
		    (V_FW_HDR_FW_VER_MAJOR(1) | V_FW_HDR_FW_VER_MINOR(20) |
		    V_FW_HDR_FW_VER_MICRO(1) | V_FW_HDR_FW_VER_BUILD(0))) {
			rc = 0;
		}
		if (rc != 0) {
			device_printf(sc->dev,
			    "failed to enable high priority filters :%d.\n",
			    rc);
		}
	}

	/* Enable opaque VIIDs with firmwares that support it. */
	param = FW_PARAM_DEV(OPAQUE_VIID_SMT_EXTN);
	val = 1;
	rc = -t4_set_params(sc, sc->mbox, sc->pf, 0, 1, &param, &val);
	if (rc == 0 && val == 1)
		sc->params.viid_smt_extn_support = true;
	else
		sc->params.viid_smt_extn_support = false;

	return (rc);
}