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
typedef  int uint16_t ;
struct ifmediareq {int dummy; } ;
struct hwrm_async_event_cmpl {int /*<<< orphan*/  event_id; } ;
struct cmpl_base {int dummy; } ;
struct bnxt_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_DCB_CONFIG_CHANGE 143 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_FUNC_DRVR_LOAD 142 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_FUNC_DRVR_UNLOAD 141 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_HWRM_ERROR 140 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_MTU_CHANGE 139 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_CHANGE 138 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_NOT_ALLOWED 137 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CHANGE 136 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_STATUS_CHANGE 135 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_LOAD 134 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_UNLOAD 133 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PF_VF_COMM_STATUS_CHANGE 132 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PORT_CONN_NOT_ALLOWED 131 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_VF_CFG_CHANGE 130 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_VF_FLR 129 
#define  HWRM_ASYNC_EVENT_CMPL_EVENT_ID_VF_MAC_ADDR_CHANGE 128 
 int /*<<< orphan*/  bnxt_media_status (int /*<<< orphan*/ ,struct ifmediareq*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_handle_async_event(struct bnxt_softc *softc, struct cmpl_base *cmpl)
{
	struct hwrm_async_event_cmpl *ae = (void *)cmpl;
	uint16_t async_id = le16toh(ae->event_id);
	struct ifmediareq ifmr;

	switch (async_id) {
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_STATUS_CHANGE:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CHANGE:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_CHANGE:
		bnxt_media_status(softc->ctx, &ifmr);
		break;
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_MTU_CHANGE:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_DCB_CONFIG_CHANGE:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PORT_CONN_NOT_ALLOWED:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_NOT_ALLOWED:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_FUNC_DRVR_UNLOAD:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_FUNC_DRVR_LOAD:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_UNLOAD:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_LOAD:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_VF_FLR:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_VF_MAC_ADDR_CHANGE:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PF_VF_COMM_STATUS_CHANGE:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_VF_CFG_CHANGE:
	case HWRM_ASYNC_EVENT_CMPL_EVENT_ID_HWRM_ERROR:
		device_printf(softc->dev,
		    "Unhandled async completion type %u\n", async_id);
		break;
	default:
		device_printf(softc->dev,
		    "Unknown async completion type %u\n", async_id);
		break;
	}
}