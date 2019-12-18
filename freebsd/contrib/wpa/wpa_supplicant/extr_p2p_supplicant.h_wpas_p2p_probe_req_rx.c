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

/* Variables and functions */

__attribute__((used)) static inline int wpas_p2p_probe_req_rx(struct wpa_supplicant *wpa_s,
					const u8 *addr,
					const u8 *dst, const u8 *bssid,
					const u8 *ie, size_t ie_len,
					unsigned int rx_freq, int ssi_signal)
{
	return 0;
}