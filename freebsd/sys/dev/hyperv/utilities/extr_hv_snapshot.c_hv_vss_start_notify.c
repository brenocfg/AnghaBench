#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  daemon_sc; int /*<<< orphan*/  app_sc; int /*<<< orphan*/  app_register_done; } ;
typedef  TYPE_1__ hv_vss_sc ;
struct TYPE_7__ {int /*<<< orphan*/  callout; TYPE_1__* sc; } ;
typedef  TYPE_2__ hv_vss_req_internal ;

/* Variables and functions */
 int TIMEOUT_LIMIT ; 
#define  VSS_OP_FREEZE 130 
#define  VSS_OP_HOT_BACKUP 129 
#define  VSS_OP_THAW 128 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hv_vss_notify (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  hv_vss_timeout ; 
 int hz ; 

__attribute__((used)) static void
hv_vss_start_notify(hv_vss_req_internal *reqp, uint32_t opt)
{
	hv_vss_sc *sc = reqp->sc;
	/*
	 * Freeze/Check notification sequence: kernel -> app -> daemon(fs)
	 * Thaw notification sequence:         kernel -> daemon(fs) -> app
	 *
	 * We should wake up the daemon, in case it's doing poll().
	 * The response should be received after 5s, otherwise, trigger timeout.
	 */
	switch (opt) {
	case VSS_OP_FREEZE:
	case VSS_OP_HOT_BACKUP:
		if (sc->app_register_done)
			hv_vss_notify(&sc->app_sc, reqp);
		else
			hv_vss_notify(&sc->daemon_sc, reqp);
		callout_reset(&reqp->callout, TIMEOUT_LIMIT * hz,
		    hv_vss_timeout, reqp);
		break;
	case VSS_OP_THAW:
		hv_vss_notify(&sc->daemon_sc, reqp);
		callout_reset(&reqp->callout, TIMEOUT_LIMIT * hz,
		    hv_vss_timeout, reqp);
		break;
	}
}