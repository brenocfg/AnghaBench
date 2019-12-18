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
typedef  int /*<<< orphan*/  u16 ;
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_disassoc_notif (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

void wpas_p2p_disassoc_notif(struct wpa_supplicant *wpa_s, const u8 *bssid,
			     u16 reason_code, const u8 *ie, size_t ie_len,
			     int locally_generated)
{
	if (wpa_s->global->p2p_disabled || wpa_s->global->p2p == NULL)
		return;

	if (!locally_generated)
		p2p_disassoc_notif(wpa_s->global->p2p, bssid, reason_code, ie,
				   ie_len);
}