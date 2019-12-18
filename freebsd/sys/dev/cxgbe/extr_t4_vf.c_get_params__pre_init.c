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
typedef  void* uint32_t ;
struct TYPE_3__ {void* cclk; } ;
struct TYPE_4__ {void* tp_vers; void* fw_vers; TYPE_1__ vpd; } ;
struct adapter {TYPE_2__ params; int /*<<< orphan*/  tp_version; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCLK ; 
 int /*<<< orphan*/  FWREV ; 
 void* FW_PARAM_DEV (int /*<<< orphan*/ ) ; 
 int G_FW_HDR_FW_VER_BUILD (void*) ; 
 int G_FW_HDR_FW_VER_MAJOR (void*) ; 
 int G_FW_HDR_FW_VER_MICRO (void*) ; 
 int G_FW_HDR_FW_VER_MINOR (void*) ; 
 int /*<<< orphan*/  TPREV ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nitems (void**) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,int) ; 
 int t4vf_query_params (struct adapter*,int /*<<< orphan*/ ,void**,void**) ; 

__attribute__((used)) static int
get_params__pre_init(struct adapter *sc)
{
	int rc;
	uint32_t param[3], val[3];

	param[0] = FW_PARAM_DEV(FWREV);
	param[1] = FW_PARAM_DEV(TPREV);
	param[2] = FW_PARAM_DEV(CCLK);
	rc = -t4vf_query_params(sc, nitems(param), param, val);
	if (rc != 0) {
		device_printf(sc->dev,
		    "failed to query parameters (pre_init): %d.\n", rc);
		return (rc);
	}

	sc->params.fw_vers = val[0];
	sc->params.tp_vers = val[1];
	sc->params.vpd.cclk = val[2];

	snprintf(sc->fw_version, sizeof(sc->fw_version), "%u.%u.%u.%u",
	    G_FW_HDR_FW_VER_MAJOR(sc->params.fw_vers),
	    G_FW_HDR_FW_VER_MINOR(sc->params.fw_vers),
	    G_FW_HDR_FW_VER_MICRO(sc->params.fw_vers),
	    G_FW_HDR_FW_VER_BUILD(sc->params.fw_vers));

	snprintf(sc->tp_version, sizeof(sc->tp_version), "%u.%u.%u.%u",
	    G_FW_HDR_FW_VER_MAJOR(sc->params.tp_vers),
	    G_FW_HDR_FW_VER_MINOR(sc->params.tp_vers),
	    G_FW_HDR_FW_VER_MICRO(sc->params.tp_vers),
	    G_FW_HDR_FW_VER_BUILD(sc->params.tp_vers));

	return (0);
}