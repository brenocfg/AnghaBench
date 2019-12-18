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
typedef  int /*<<< orphan*/  u32 ;
struct vlan_description {int dummy; } ;
struct os_reltime {int dummy; } ;
struct hostapd_sta_wpa_psk_short {int dummy; } ;
struct hostapd_data {struct hostapd_cached_radius_acl* acl_cache; } ;
struct hostapd_cached_radius_acl {scalar_t__ accepted; scalar_t__ radius_cui; scalar_t__ identity; int /*<<< orphan*/  psk; struct vlan_description vlan_id; int /*<<< orphan*/  acct_interim_interval; int /*<<< orphan*/  session_timeout; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  addr; struct hostapd_cached_radius_acl* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ HOSTAPD_ACL_ACCEPT_TIMEOUT ; 
 int /*<<< orphan*/  RADIUS_ACL_TIMEOUT ; 
 int /*<<< orphan*/  copy_psk_list (struct hostapd_sta_wpa_psk_short**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_reltime_expired (struct os_reltime*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* os_strdup (scalar_t__) ; 

__attribute__((used)) static int hostapd_acl_cache_get(struct hostapd_data *hapd, const u8 *addr,
				 u32 *session_timeout,
				 u32 *acct_interim_interval,
				 struct vlan_description *vlan_id,
				 struct hostapd_sta_wpa_psk_short **psk,
				 char **identity, char **radius_cui)
{
	struct hostapd_cached_radius_acl *entry;
	struct os_reltime now;

	os_get_reltime(&now);

	for (entry = hapd->acl_cache; entry; entry = entry->next) {
		if (os_memcmp(entry->addr, addr, ETH_ALEN) != 0)
			continue;

		if (os_reltime_expired(&now, &entry->timestamp,
				       RADIUS_ACL_TIMEOUT))
			return -1; /* entry has expired */
		if (entry->accepted == HOSTAPD_ACL_ACCEPT_TIMEOUT)
			if (session_timeout)
				*session_timeout = entry->session_timeout;
		if (acct_interim_interval)
			*acct_interim_interval =
				entry->acct_interim_interval;
		if (vlan_id)
			*vlan_id = entry->vlan_id;
		copy_psk_list(psk, entry->psk);
		if (identity) {
			if (entry->identity)
				*identity = os_strdup(entry->identity);
			else
				*identity = NULL;
		}
		if (radius_cui) {
			if (entry->radius_cui)
				*radius_cui = os_strdup(entry->radius_cui);
			else
				*radius_cui = NULL;
		}
		return entry->accepted;
	}

	return -1;
}