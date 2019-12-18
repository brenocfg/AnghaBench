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
struct twa_softc {int /*<<< orphan*/  bus_dev; int /*<<< orphan*/  ctlr_handle; int /*<<< orphan*/ * watchdog_callout; int /*<<< orphan*/  watchdog_index; struct tw_osli_req_context* req_ctx_buf; } ;
struct tw_osli_req_context {scalar_t__ state; scalar_t__ deadline; } ;
struct tw_cl_ctlr_handle {struct twa_softc* osl_ctlr_ctxt; } ;
typedef  int /*<<< orphan*/  TW_VOID ;
typedef  scalar_t__ TW_UINT64 ;

/* Variables and functions */
 int TW_OSLI_MAX_NUM_REQUESTS ; 
 scalar_t__ TW_OSLI_REQ_STATE_BUSY ; 
 int callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int hz ; 
 int tw_cl_is_active (struct tw_cl_ctlr_handle*) ; 
 int tw_cl_is_reset_needed (struct tw_cl_ctlr_handle*) ; 
 int /*<<< orphan*/  tw_cl_reset_ctlr (struct tw_cl_ctlr_handle*) ; 
 int /*<<< orphan*/  tw_cl_set_reset_needed (struct tw_cl_ctlr_handle*) ; 
 scalar_t__ tw_osl_get_local_time () ; 

__attribute__((used)) static TW_VOID
twa_watchdog(TW_VOID *arg)
{
	struct tw_cl_ctlr_handle *ctlr_handle =
		(struct tw_cl_ctlr_handle *)arg;
	struct twa_softc		*sc = ctlr_handle->osl_ctlr_ctxt;
	int				i;
	int				i_need_a_reset = 0;
	int				driver_is_active = 0;
	int				my_watchdog_was_pending = 1234;
	TW_UINT64			current_time;
	struct tw_osli_req_context	*my_req;


//==============================================================================
	current_time = (TW_UINT64) (tw_osl_get_local_time());

	for (i = 0; i < TW_OSLI_MAX_NUM_REQUESTS; i++) {
		my_req = &(sc->req_ctx_buf[i]);

		if ((my_req->state == TW_OSLI_REQ_STATE_BUSY) &&
			(my_req->deadline) &&
			(my_req->deadline < current_time)) {
			tw_cl_set_reset_needed(ctlr_handle);
#ifdef    TW_OSL_DEBUG
			device_printf((sc)->bus_dev, "Request %d timed out! d = %llu, c = %llu\n", i, my_req->deadline, current_time);
#else  /* TW_OSL_DEBUG */
			device_printf((sc)->bus_dev, "Request %d timed out!\n", i);
#endif /* TW_OSL_DEBUG */
			break;
		}
	}
//==============================================================================

	i_need_a_reset = tw_cl_is_reset_needed(ctlr_handle);

	i = (int) ((sc->watchdog_index++) & 1);

	driver_is_active = tw_cl_is_active(ctlr_handle);

	if (i_need_a_reset) {
#ifdef    TW_OSL_DEBUG
		device_printf((sc)->bus_dev, "Watchdog rescheduled in 70 seconds\n");
#endif /* TW_OSL_DEBUG */
		my_watchdog_was_pending =
			callout_reset(&(sc->watchdog_callout[i]), 70*hz, twa_watchdog, &sc->ctlr_handle);
		tw_cl_reset_ctlr(ctlr_handle);
#ifdef    TW_OSL_DEBUG
		device_printf((sc)->bus_dev, "Watchdog reset completed!\n");
#endif /* TW_OSL_DEBUG */
	} else if (driver_is_active) {
		my_watchdog_was_pending =
			callout_reset(&(sc->watchdog_callout[i]),  5*hz, twa_watchdog, &sc->ctlr_handle);
	}
#ifdef    TW_OSL_DEBUG
	if (i_need_a_reset || my_watchdog_was_pending)
		device_printf((sc)->bus_dev, "i_need_a_reset = %d, "
		"driver_is_active = %d, my_watchdog_was_pending = %d\n",
		i_need_a_reset, driver_is_active, my_watchdog_was_pending);
#endif /* TW_OSL_DEBUG */
}