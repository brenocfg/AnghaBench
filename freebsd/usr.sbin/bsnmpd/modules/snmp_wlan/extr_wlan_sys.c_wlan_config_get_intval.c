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
struct wlan_iface {int /*<<< orphan*/  wname; } ;

/* Variables and functions */
 scalar_t__ wlan_config_check (struct wlan_iface*,int) ; 
 int /*<<< orphan*/  wlan_config_set_snmp_intval (struct wlan_iface*,int,int) ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wlan_config_get_intval(struct wlan_iface *wif, int op)
{
	int val = 0;
	size_t argsize = 0;

	if (wlan_config_check(wif, op) < 0)
		return (0);
	if (wlan_ioctl(wif->wname, op, &val, NULL, &argsize, 0) < 0)
		return (-1);
	wlan_config_set_snmp_intval(wif, op, val);

	return (0);
}