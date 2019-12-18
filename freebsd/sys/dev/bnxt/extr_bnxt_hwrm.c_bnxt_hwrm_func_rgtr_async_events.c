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
typedef  int /*<<< orphan*/  uint32_t ;
struct hwrm_func_drv_rgtr_input {int /*<<< orphan*/ * async_event_fwd; int /*<<< orphan*/  enables; int /*<<< orphan*/  member_0; } ;
struct bnxt_softc {int dummy; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  bitstr_t ;

/* Variables and functions */
 int HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_CHANGE ; 
 int HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_STATUS_CHANGE ; 
 int HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_UNLOAD ; 
 int HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PORT_CONN_NOT_ALLOWED ; 
 int HWRM_ASYNC_EVENT_CMPL_EVENT_ID_VF_CFG_CHANGE ; 
 int /*<<< orphan*/  HWRM_FUNC_DRV_RGTR ; 
 int /*<<< orphan*/  HWRM_FUNC_DRV_RGTR_INPUT_ENABLES_ASYNC_EVENT_FWD ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * bit_alloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bit_test (unsigned long*,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_func_drv_rgtr_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt_softc*,struct hwrm_func_drv_rgtr_input*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int bnxt_hwrm_func_rgtr_async_events(struct bnxt_softc *softc, unsigned long *bmap,
                                     int bmap_size)
{
	struct hwrm_func_drv_rgtr_input req = {0};
	bitstr_t *async_events_bmap;
	uint32_t *events;
	int i;

	async_events_bmap = bit_alloc(256, M_DEVBUF, M_WAITOK|M_ZERO);
	events = (uint32_t *)async_events_bmap;

	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_FUNC_DRV_RGTR);

	req.enables =
		htole32(HWRM_FUNC_DRV_RGTR_INPUT_ENABLES_ASYNC_EVENT_FWD);

	memset(async_events_bmap, 0, sizeof(256 / 8));

	bit_set(async_events_bmap, HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_STATUS_CHANGE);
	bit_set(async_events_bmap, HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PF_DRVR_UNLOAD);
	bit_set(async_events_bmap, HWRM_ASYNC_EVENT_CMPL_EVENT_ID_PORT_CONN_NOT_ALLOWED);
	bit_set(async_events_bmap, HWRM_ASYNC_EVENT_CMPL_EVENT_ID_VF_CFG_CHANGE);
	bit_set(async_events_bmap, HWRM_ASYNC_EVENT_CMPL_EVENT_ID_LINK_SPEED_CFG_CHANGE);

	if (bmap && bmap_size) {
		for (i = 0; i < bmap_size; i++) {
			if (bit_test(bmap, i))
				bit_set(async_events_bmap, i);
		}
	}

	for (i = 0; i < 8; i++)
		req.async_event_fwd[i] |= htole32(events[i]);

	free(async_events_bmap, M_DEVBUF);

	return hwrm_send_message(softc, &req, sizeof(req));
}