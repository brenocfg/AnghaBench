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
struct eapol_test_data {int /*<<< orphan*/  wpa_s; scalar_t__ radius_access_accept_received; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  send_eap_request_identity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eapol_sm_reauth(void *eloop_ctx, void *timeout_ctx)
{
	struct eapol_test_data *e = eloop_ctx;
	printf("\n\n\n\n\neapol_test: Triggering EAP reauthentication\n\n");
	e->radius_access_accept_received = 0;
	send_eap_request_identity(e->wpa_s, NULL);
}