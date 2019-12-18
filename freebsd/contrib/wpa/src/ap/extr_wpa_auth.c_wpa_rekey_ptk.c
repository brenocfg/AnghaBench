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
struct wpa_state_machine {int /*<<< orphan*/  addr; } ;
struct wpa_authenticator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG ; 
 int /*<<< orphan*/  wpa_auth_logger (struct wpa_authenticator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_request_new_ptk (struct wpa_state_machine*) ; 
 int /*<<< orphan*/  wpa_sm_step (struct wpa_state_machine*) ; 

__attribute__((used)) static void wpa_rekey_ptk(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_authenticator *wpa_auth = eloop_ctx;
	struct wpa_state_machine *sm = timeout_ctx;

	wpa_auth_logger(wpa_auth, sm->addr, LOGGER_DEBUG, "rekeying PTK");
	wpa_request_new_ptk(sm);
	wpa_sm_step(sm);
}