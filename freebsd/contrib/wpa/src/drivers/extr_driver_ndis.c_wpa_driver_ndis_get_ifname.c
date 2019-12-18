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
struct wpa_driver_ndis_data {char const* ifname; } ;

/* Variables and functions */

__attribute__((used)) static const char * wpa_driver_ndis_get_ifname(void *priv)
{
	struct wpa_driver_ndis_data *drv = priv;
	return drv->ifname;
}