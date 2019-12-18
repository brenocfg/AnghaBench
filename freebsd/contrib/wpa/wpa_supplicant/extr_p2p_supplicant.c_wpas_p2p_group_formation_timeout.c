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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_p2p_group_formation_failed (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_p2p_group_formation_timeout(void *eloop_ctx,
					     void *timeout_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;
	wpa_printf(MSG_DEBUG, "P2P: Group Formation timed out");
	wpas_p2p_group_formation_failed(wpa_s, 0);
}