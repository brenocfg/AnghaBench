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
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {char const* iface; } ;

/* Variables and functions */

__attribute__((used)) static const char * hostapd_msg_ifname_cb(void *ctx)
{
	struct hostapd_data *hapd = ctx;
	if (hapd && hapd->conf)
		return hapd->conf->iface;
	return NULL;
}