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
typedef  scalar_t__ uint ;
struct wlan_mesh_route {int dummy; } ;
struct wlan_iface {int /*<<< orphan*/  mesh_routelist; } ;
struct asn_oid {scalar_t__ len; } ;

/* Variables and functions */
 int IEEE80211_ADDR_LEN ; 
 int IFNAMSIZ ; 
 struct wlan_mesh_route* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct wlan_mesh_route* SLIST_NEXT (struct wlan_mesh_route*,int /*<<< orphan*/ ) ; 
 struct wlan_iface* wlan_find_interface (char*) ; 
 scalar_t__ wlan_mac_index_decode (struct asn_oid const*,scalar_t__,char*,char*) ; 
 struct wlan_mesh_route* wlan_mesh_find_route (struct wlan_iface*,char*) ; 
 struct wlan_iface* wlan_mesh_first_interface () ; 
 struct wlan_iface* wlan_mesh_next_interface (struct wlan_iface*) ; 
 int /*<<< orphan*/  wr ; 

__attribute__((used)) static struct wlan_mesh_route *
wlan_mesh_get_next_route(const struct asn_oid *oid, uint sub,
    struct wlan_iface **wif)
{
	char wname[IFNAMSIZ];
	char dstmac[IEEE80211_ADDR_LEN];
	struct wlan_mesh_route *wmr;

	if (oid->len - sub == 0) {
		for (*wif = wlan_mesh_first_interface(); *wif != NULL;
		    *wif = wlan_mesh_next_interface(*wif)) {
			wmr = SLIST_FIRST(&(*wif)->mesh_routelist);
			if (wmr != NULL)
				return (wmr);
		}
		return (NULL);
	}

	if (wlan_mac_index_decode(oid, sub, wname, dstmac) < 0 ||
	    (*wif = wlan_find_interface(wname)) == NULL ||
	    (wmr = wlan_mesh_find_route(*wif, dstmac)) == NULL)
		return (NULL);

	if ((wmr = SLIST_NEXT(wmr, wr)) != NULL)
		return (wmr);

	while ((*wif = wlan_mesh_next_interface(*wif)) != NULL)
		if ((wmr = SLIST_FIRST(&(*wif)->mesh_routelist)) != NULL)
			break;

	return (wmr);
}