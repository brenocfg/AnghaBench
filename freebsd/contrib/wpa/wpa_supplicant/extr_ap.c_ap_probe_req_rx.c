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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {TYPE_1__* ap_iface; } ;
struct TYPE_2__ {unsigned int freq; } ;

/* Variables and functions */
 int wpas_p2p_probe_req_rx (struct wpa_supplicant*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,unsigned int,int) ; 

__attribute__((used)) static int ap_probe_req_rx(void *ctx, const u8 *sa, const u8 *da,
			   const u8 *bssid, const u8 *ie, size_t ie_len,
			   int ssi_signal)
{
	struct wpa_supplicant *wpa_s = ctx;
	unsigned int freq = 0;

	if (wpa_s->ap_iface)
		freq = wpa_s->ap_iface->freq;

	return wpas_p2p_probe_req_rx(wpa_s, sa, da, bssid, ie, ie_len,
				     freq, ssi_signal);
}