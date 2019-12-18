#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {TYPE_2__* p2p_send_action_work; TYPE_1__* p2p_listen_work; } ;
struct TYPE_4__ {int freq; } ;
struct TYPE_3__ {int freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int offchannel_send_action (struct wpa_supplicant*,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpas_p2p_send_action_tx_status ; 
 int wpas_send_action_work (struct wpa_supplicant*,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,unsigned int) ; 

__attribute__((used)) static int wpas_send_action(void *ctx, unsigned int freq, const u8 *dst,
			    const u8 *src, const u8 *bssid, const u8 *buf,
			    size_t len, unsigned int wait_time, int *scheduled)
{
	struct wpa_supplicant *wpa_s = ctx;
	int listen_freq = -1, send_freq = -1;

	if (scheduled)
		*scheduled = 0;
	if (wpa_s->p2p_listen_work)
		listen_freq = wpa_s->p2p_listen_work->freq;
	if (wpa_s->p2p_send_action_work)
		send_freq = wpa_s->p2p_send_action_work->freq;
	if (listen_freq != (int) freq && send_freq != (int) freq) {
		int res;

		wpa_printf(MSG_DEBUG, "P2P: Schedule new radio work for Action frame TX (listen_freq=%d send_freq=%d freq=%u)",
			   listen_freq, send_freq, freq);
		res = wpas_send_action_work(wpa_s, freq, dst, src, bssid, buf,
					    len, wait_time);
		if (res == 0 && scheduled)
			*scheduled = 1;
		return res;
	}

	wpa_printf(MSG_DEBUG, "P2P: Use ongoing radio work for Action frame TX");
	return offchannel_send_action(wpa_s, freq, dst, src, bssid, buf, len,
				      wait_time,
				      wpas_p2p_send_action_tx_status, 1);
}