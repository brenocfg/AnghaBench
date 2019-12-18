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
struct wpa_supplicant {int drv_flags; scalar_t__ action_tx_wait_time_used; scalar_t__ roc_waiting_drv_freq; scalar_t__ off_channel_freq; scalar_t__ action_tx_wait_time; int /*<<< orphan*/ * pending_action_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_DRIVER_FLAGS_OFFCHANNEL_TX ; 
 int /*<<< orphan*/  wpa_drv_cancel_remain_on_channel (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_drv_send_action_cancel_wait (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

void offchannel_send_action_done(struct wpa_supplicant *wpa_s)
{
	wpa_printf(MSG_DEBUG,
		   "Off-channel: Action frame sequence done notification: pending_action_tx=%p drv_offchan_tx=%d action_tx_wait_time=%d off_channel_freq=%d roc_waiting_drv_freq=%d",
		   wpa_s->pending_action_tx,
		   !!(wpa_s->drv_flags & WPA_DRIVER_FLAGS_OFFCHANNEL_TX),
		   wpa_s->action_tx_wait_time, wpa_s->off_channel_freq,
		   wpa_s->roc_waiting_drv_freq);
	wpabuf_free(wpa_s->pending_action_tx);
	wpa_s->pending_action_tx = NULL;
	if (wpa_s->drv_flags & WPA_DRIVER_FLAGS_OFFCHANNEL_TX &&
	    (wpa_s->action_tx_wait_time || wpa_s->action_tx_wait_time_used))
		wpa_drv_send_action_cancel_wait(wpa_s);
	else if (wpa_s->off_channel_freq || wpa_s->roc_waiting_drv_freq) {
		wpa_drv_cancel_remain_on_channel(wpa_s);
		wpa_s->off_channel_freq = 0;
		wpa_s->roc_waiting_drv_freq = 0;
	}
	wpa_s->action_tx_wait_time_used = 0;
}