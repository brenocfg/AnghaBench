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
typedef  int /*<<< orphan*/  uint ;
struct wlan_iface {scalar_t__ mode; } ;
struct asn_oid {int dummy; } ;

/* Variables and functions */
 scalar_t__ WlanIfaceOperatingModeType_meshPoint ; 
 struct wlan_iface* wlan_get_interface (struct asn_oid const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wlan_iface *
wlan_mesh_get_iface(const struct asn_oid *oid, uint sub)
{
	struct wlan_iface *wif;

	if ((wif = wlan_get_interface(oid, sub)) == NULL)
		return (NULL);

	if (wif->mode != WlanIfaceOperatingModeType_meshPoint)
		return (NULL);

	return (wif);
}