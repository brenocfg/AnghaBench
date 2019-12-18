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
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_rx_action (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int) ; 

void wpas_p2p_rx_action(struct wpa_supplicant *wpa_s, const u8 *da,
			const u8 *sa, const u8 *bssid,
			u8 category, const u8 *data, size_t len, int freq)
{
	if (wpa_s->global->p2p_disabled)
		return;
	if (wpa_s->global->p2p == NULL)
		return;

	p2p_rx_action(wpa_s->global->p2p, da, sa, bssid, category, data, len,
		      freq);
}