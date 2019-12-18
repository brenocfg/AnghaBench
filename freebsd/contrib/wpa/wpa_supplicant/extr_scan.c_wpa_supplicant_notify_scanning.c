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
struct wpa_supplicant {int scanning; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_notify_scanning (struct wpa_supplicant*) ; 

void wpa_supplicant_notify_scanning(struct wpa_supplicant *wpa_s,
				    int scanning)
{
	if (wpa_s->scanning != scanning) {
		wpa_s->scanning = scanning;
		wpas_notify_scanning(wpa_s);
	}
}