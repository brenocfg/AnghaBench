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
struct wpa_supplicant {int /*<<< orphan*/  wpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int,void (*) (void*,void*),void*,void*) ; 
 int /*<<< orphan*/  eloop_terminate () ; 
 int /*<<< orphan*/  rsn_preauth_in_progress (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eapol_test_poll(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;
	if (!rsn_preauth_in_progress(wpa_s->wpa))
		eloop_terminate();
	else {
		eloop_register_timeout(0, 100000, eapol_test_poll, eloop_ctx,
				       timeout_ctx);
	}
}