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
struct wpa_supplicant {scalar_t__ p2p_lo_started; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int wpa_drv_p2p_lo_stop (struct wpa_supplicant*) ; 

int wpas_p2p_lo_stop(struct wpa_supplicant *wpa_s)
{
	int ret;

	if (!wpa_s->p2p_lo_started)
		return 0;

	ret = wpa_drv_p2p_lo_stop(wpa_s);
	if (ret < 0)
		wpa_dbg(wpa_s, MSG_DEBUG,
			"P2P: Failed to stop P2P listen offload");

	wpa_s->p2p_lo_started = 0;
	return ret;
}