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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_ssid_value {int dummy; } ;
struct hostapd_neighbor_entry {int /*<<< orphan*/  list; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_neighbor_clear_entry (struct hostapd_neighbor_entry*) ; 
 struct hostapd_neighbor_entry* hostapd_neighbor_get (struct hostapd_data*,int /*<<< orphan*/  const*,struct wpa_ssid_value const*) ; 
 int /*<<< orphan*/  os_free (struct hostapd_neighbor_entry*) ; 

int hostapd_neighbor_remove(struct hostapd_data *hapd, const u8 *bssid,
			    const struct wpa_ssid_value *ssid)
{
	struct hostapd_neighbor_entry *nr;

	nr = hostapd_neighbor_get(hapd, bssid, ssid);
	if (!nr)
		return -1;

	hostapd_neighbor_clear_entry(nr);
	dl_list_del(&nr->list);
	os_free(nr);

	return 0;
}