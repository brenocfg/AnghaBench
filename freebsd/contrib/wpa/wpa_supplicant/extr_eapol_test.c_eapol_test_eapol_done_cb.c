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
struct eapol_test_data {int /*<<< orphan*/  wpa_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_COMPLETED ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  wpa_supplicant_cancel_auth_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eapol_test_eapol_done_cb(void *ctx)
{
	struct eapol_test_data *e = ctx;

	printf("WPA: EAPOL processing complete\n");
	wpa_supplicant_cancel_auth_timeout(e->wpa_s);
	wpa_supplicant_set_state(e->wpa_s, WPA_COMPLETED);
}