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
typedef  char uint8_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ uint ;
struct wlan_iface {int dummy; } ;
struct asn_oid {scalar_t__ len; scalar_t__* subs; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct wlan_iface* wlan_find_interface (char*) ; 
 struct wlan_iface* wlan_mesh_first_interface () ; 
 struct wlan_iface* wlan_mesh_next_interface (struct wlan_iface*) ; 

__attribute__((used)) static struct wlan_iface *
wlan_mesh_get_next_iface(const struct asn_oid *oid, uint sub)
{
	uint32_t i;
	uint8_t wname[IFNAMSIZ];
	struct wlan_iface *wif;

	if (oid->len - sub == 0)
		return (wlan_mesh_first_interface());

	if (oid->len - sub != oid->subs[sub] + 1 || oid->subs[sub] >= IFNAMSIZ)
		return (NULL);

	memset(wname, 0, IFNAMSIZ);
	for (i = 0; i < oid->subs[sub]; i++)
		wname[i] = oid->subs[sub + i + 1];
	wname[i] = '\0';

	if ((wif = wlan_find_interface(wname)) == NULL)
		return (NULL);

	return (wlan_mesh_next_interface(wif));
}