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
struct wpa_supplicant {char const* ifname; } ;

/* Variables and functions */

__attribute__((used)) static const char * wpa_supplicant_msg_ifname_cb(void *ctx)
{
	struct wpa_supplicant *wpa_s = ctx;
	if (wpa_s == NULL)
		return NULL;
	return wpa_s->ifname;
}