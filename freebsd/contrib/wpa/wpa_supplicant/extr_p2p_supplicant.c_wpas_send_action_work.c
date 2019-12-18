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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int dummy; } ;
struct send_action_work {unsigned int freq; size_t len; unsigned int wait_time; int /*<<< orphan*/  buf; int /*<<< orphan*/  bssid; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (struct send_action_work*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 struct send_action_work* os_zalloc (int) ; 
 scalar_t__ radio_add_work (struct wpa_supplicant*,unsigned int,char*,int,int /*<<< orphan*/ ,struct send_action_work*) ; 
 scalar_t__ radio_work_pending (struct wpa_supplicant*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_send_action_cb ; 

__attribute__((used)) static int wpas_send_action_work(struct wpa_supplicant *wpa_s,
				 unsigned int freq, const u8 *dst,
				 const u8 *src, const u8 *bssid, const u8 *buf,
				 size_t len, unsigned int wait_time)
{
	struct send_action_work *awork;

	if (radio_work_pending(wpa_s, "p2p-send-action")) {
		wpa_printf(MSG_DEBUG, "P2P: Cannot schedule new p2p-send-action work since one is already pending");
		return -1;
	}

	awork = os_zalloc(sizeof(*awork) + len);
	if (awork == NULL)
		return -1;

	awork->freq = freq;
	os_memcpy(awork->dst, dst, ETH_ALEN);
	os_memcpy(awork->src, src, ETH_ALEN);
	os_memcpy(awork->bssid, bssid, ETH_ALEN);
	awork->len = len;
	awork->wait_time = wait_time;
	os_memcpy(awork->buf, buf, len);

	if (radio_add_work(wpa_s, freq, "p2p-send-action", 1,
			   wpas_send_action_cb, awork) < 0) {
		os_free(awork);
		return -1;
	}

	return 0;
}