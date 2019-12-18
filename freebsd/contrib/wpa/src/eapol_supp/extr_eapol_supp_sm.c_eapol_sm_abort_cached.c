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
struct eapol_sm {int startWhen; TYPE_1__* ctx; int /*<<< orphan*/  SUPP_PAE_state; int /*<<< orphan*/  cached_pmk; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* aborted_cached ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SUPP_PAE_CONNECTING ; 
 int /*<<< orphan*/  eapol_enable_timer_tick (struct eapol_sm*) ; 
 int /*<<< orphan*/  eapol_sm_set_port_unauthorized (struct eapol_sm*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eapol_sm_abort_cached(struct eapol_sm *sm)
{
	wpa_printf(MSG_DEBUG, "RSN: Authenticator did not accept PMKID, "
		   "doing full EAP authentication");
	if (sm == NULL)
		return;
	sm->cached_pmk = FALSE;
	sm->SUPP_PAE_state = SUPP_PAE_CONNECTING;
	eapol_sm_set_port_unauthorized(sm);

	/* Make sure we do not start sending EAPOL-Start frames first, but
	 * instead move to RESTART state to start EAPOL authentication. */
	sm->startWhen = 3;
	eapol_enable_timer_tick(sm);

	if (sm->ctx->aborted_cached)
		sm->ctx->aborted_cached(sm->ctx->ctx);
}