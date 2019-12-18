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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_ssid {scalar_t__ ssid_len; int /*<<< orphan*/ * ssid; struct wpa_ssid* next; } ;
struct wpa_bss {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_2__ {struct wpa_ssid* ssid; } ;

/* Variables and functions */
 scalar_t__ os_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int wpa_bss_known(struct wpa_supplicant *wpa_s, struct wpa_bss *bss)
{
	struct wpa_ssid *ssid;

	for (ssid = wpa_s->conf->ssid; ssid; ssid = ssid->next) {
		if (ssid->ssid == NULL || ssid->ssid_len == 0)
			continue;
		if (ssid->ssid_len == bss->ssid_len &&
		    os_memcmp(ssid->ssid, bss->ssid, ssid->ssid_len) == 0)
			return 1;
	}

	return 0;
}