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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_scan_ie (int /*<<< orphan*/ *,struct wpabuf*,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int wpas_get_bands (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 

void wpas_p2p_scan_ie(struct wpa_supplicant *wpa_s, struct wpabuf *ies)
{
	unsigned int bands;

	if (wpa_s->global->p2p_disabled)
		return;
	if (wpa_s->global->p2p == NULL)
		return;

	bands = wpas_get_bands(wpa_s, NULL);
	p2p_scan_ie(wpa_s->global->p2p, ies, NULL, bands);
}