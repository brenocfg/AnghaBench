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
struct wpa_pmkid_params {int /*<<< orphan*/ * pmkid; int /*<<< orphan*/ * bssid; } ;
struct wpa_driver_ndis_data {scalar_t__ no_of_pmkid; struct ndis_pmkid_entry* pmkid; } ;
struct ndis_pmkid_entry {struct ndis_pmkid_entry* next; int /*<<< orphan*/  pmkid; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 struct ndis_pmkid_entry* os_malloc (int) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int wpa_driver_ndis_set_pmkid (struct wpa_driver_ndis_data*) ; 

__attribute__((used)) static int wpa_driver_ndis_add_pmkid(void *priv,
				     struct wpa_pmkid_params *params)
{
	struct wpa_driver_ndis_data *drv = priv;
	struct ndis_pmkid_entry *entry, *prev;
	const u8 *bssid = params->bssid;
	const u8 *pmkid = params->pmkid;

	if (!bssid || !pmkid)
		return -1;
	if (drv->no_of_pmkid == 0)
		return 0;

	prev = NULL;
	entry = drv->pmkid;
	while (entry) {
		if (os_memcmp(entry->bssid, bssid, ETH_ALEN) == 0)
			break;
		prev = entry;
		entry = entry->next;
	}

	if (entry) {
		/* Replace existing entry for this BSSID and move it into the
		 * beginning of the list. */
		os_memcpy(entry->pmkid, pmkid, 16);
		if (prev) {
			prev->next = entry->next;
			entry->next = drv->pmkid;
			drv->pmkid = entry;
		}
	} else {
		entry = os_malloc(sizeof(*entry));
		if (entry) {
			os_memcpy(entry->bssid, bssid, ETH_ALEN);
			os_memcpy(entry->pmkid, pmkid, 16);
			entry->next = drv->pmkid;
			drv->pmkid = entry;
		}
	}

	return wpa_driver_ndis_set_pmkid(drv);
}