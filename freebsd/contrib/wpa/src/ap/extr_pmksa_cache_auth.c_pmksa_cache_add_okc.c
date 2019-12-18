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
struct vlan_description {int dummy; } ;
struct rsn_pmksa_cache_entry {int opportunistic; int /*<<< orphan*/ * vlan_desc; int /*<<< orphan*/  eap_type_authsrv; int /*<<< orphan*/  radius_class; scalar_t__ cui; int /*<<< orphan*/  identity_len; int /*<<< orphan*/  const* identity; int /*<<< orphan*/  const* spa; int /*<<< orphan*/  akmp; int /*<<< orphan*/  expiration; int /*<<< orphan*/  pmk_len; int /*<<< orphan*/  const* pmk; int /*<<< orphan*/  const* pmkid; } ;
struct rsn_pmksa_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  PMKID_LEN ; 
 int /*<<< orphan*/  const* os_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 void* os_zalloc (int) ; 
 int /*<<< orphan*/  pmksa_cache_link_entry (struct rsn_pmksa_cache*,struct rsn_pmksa_cache_entry*) ; 
 int /*<<< orphan*/  radius_copy_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wpabuf_dup (scalar_t__) ; 

struct rsn_pmksa_cache_entry *
pmksa_cache_add_okc(struct rsn_pmksa_cache *pmksa,
		    const struct rsn_pmksa_cache_entry *old_entry,
		    const u8 *aa, const u8 *pmkid)
{
	struct rsn_pmksa_cache_entry *entry;

	entry = os_zalloc(sizeof(*entry));
	if (entry == NULL)
		return NULL;
	os_memcpy(entry->pmkid, pmkid, PMKID_LEN);
	os_memcpy(entry->pmk, old_entry->pmk, old_entry->pmk_len);
	entry->pmk_len = old_entry->pmk_len;
	entry->expiration = old_entry->expiration;
	entry->akmp = old_entry->akmp;
	os_memcpy(entry->spa, old_entry->spa, ETH_ALEN);
	entry->opportunistic = 1;
	if (old_entry->identity) {
		entry->identity = os_malloc(old_entry->identity_len);
		if (entry->identity) {
			entry->identity_len = old_entry->identity_len;
			os_memcpy(entry->identity, old_entry->identity,
				  old_entry->identity_len);
		}
	}
	if (old_entry->cui)
		entry->cui = wpabuf_dup(old_entry->cui);
#ifndef CONFIG_NO_RADIUS
	radius_copy_class(&entry->radius_class, &old_entry->radius_class);
#endif /* CONFIG_NO_RADIUS */
	entry->eap_type_authsrv = old_entry->eap_type_authsrv;
	if (old_entry->vlan_desc) {
		entry->vlan_desc = os_zalloc(sizeof(struct vlan_description));
		if (entry->vlan_desc)
			*entry->vlan_desc = *old_entry->vlan_desc;
	} else {
		entry->vlan_desc = NULL;
	}
	entry->opportunistic = 1;

	pmksa_cache_link_entry(pmksa, entry);

	return entry;
}