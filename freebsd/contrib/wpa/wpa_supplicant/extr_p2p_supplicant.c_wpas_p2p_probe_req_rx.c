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
struct wpa_supplicant {int /*<<< orphan*/  p2p_lo_started; TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; } ;

/* Variables and functions */
#define  P2P_PREQ_MALFORMED 132 
#define  P2P_PREQ_NOT_LISTEN 131 
#define  P2P_PREQ_NOT_P2P 130 
#define  P2P_PREQ_NOT_PROCESSED 129 
#define  P2P_PREQ_PROCESSED 128 
 int p2p_probe_req_rx (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_notify_preq (struct wpa_supplicant*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int) ; 

int wpas_p2p_probe_req_rx(struct wpa_supplicant *wpa_s, const u8 *addr,
			  const u8 *dst, const u8 *bssid,
			  const u8 *ie, size_t ie_len,
			  unsigned int rx_freq, int ssi_signal)
{
	if (wpa_s->global->p2p_disabled)
		return 0;
	if (wpa_s->global->p2p == NULL)
		return 0;

	switch (p2p_probe_req_rx(wpa_s->global->p2p, addr, dst, bssid,
				 ie, ie_len, rx_freq, wpa_s->p2p_lo_started)) {
	case P2P_PREQ_NOT_P2P:
		wpas_notify_preq(wpa_s, addr, dst, bssid, ie, ie_len,
				 ssi_signal);
		/* fall through */
	case P2P_PREQ_MALFORMED:
	case P2P_PREQ_NOT_LISTEN:
	case P2P_PREQ_NOT_PROCESSED:
	default: /* make gcc happy */
		return 0;
	case P2P_PREQ_PROCESSED:
		return 1;
	}
}