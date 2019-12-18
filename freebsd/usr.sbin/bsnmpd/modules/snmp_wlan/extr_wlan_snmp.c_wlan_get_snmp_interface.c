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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint ;
struct wlan_iface {int /*<<< orphan*/  wname; } ;
struct asn_oid {int dummy; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wlan_iface* wlan_first_interface () ; 
 int /*<<< orphan*/ * wlan_get_ifname (struct asn_oid const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wlan_iface* wlan_next_interface (struct wlan_iface*) ; 

__attribute__((used)) static struct wlan_iface *
wlan_get_snmp_interface(const struct asn_oid *oid, uint sub)
{
	uint8_t wname[IFNAMSIZ];
	struct wlan_iface *wif;

	if (wlan_get_ifname(oid, sub, wname) == NULL)
		return (NULL);

	for (wif = wlan_first_interface(); wif != NULL;
	    wif = wlan_next_interface(wif))
		if (strcmp(wif->wname, wname) == 0)
			break;

	return (wif);
}