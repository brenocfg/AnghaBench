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
struct vlan_description {scalar_t__ notempty; } ;
struct sta_info {struct vlan_description* vlan_desc; } ;
struct rsn_pmksa_cache_entry {int /*<<< orphan*/  acct_multi_session_id; struct vlan_description* vlan_desc; int /*<<< orphan*/  eap_type_authsrv; int /*<<< orphan*/  radius_class; int /*<<< orphan*/  cui; scalar_t__ identity; int /*<<< orphan*/  identity_len; } ;
struct eapol_state_machine {int /*<<< orphan*/  acct_multi_session_id; scalar_t__ sta; int /*<<< orphan*/  eap_type_authsrv; int /*<<< orphan*/  radius_class; scalar_t__ radius_cui; int /*<<< orphan*/  identity_len; scalar_t__ identity; } ;

/* Variables and functions */
 scalar_t__ os_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct vlan_description* os_zalloc (int) ; 
 int /*<<< orphan*/  radius_copy_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_dup (scalar_t__) ; 

__attribute__((used)) static void pmksa_cache_from_eapol_data(struct rsn_pmksa_cache_entry *entry,
					struct eapol_state_machine *eapol)
{
	struct vlan_description *vlan_desc;

	if (eapol == NULL)
		return;

	if (eapol->identity) {
		entry->identity = os_malloc(eapol->identity_len);
		if (entry->identity) {
			entry->identity_len = eapol->identity_len;
			os_memcpy(entry->identity, eapol->identity,
				  eapol->identity_len);
		}
	}

	if (eapol->radius_cui)
		entry->cui = wpabuf_dup(eapol->radius_cui);

#ifndef CONFIG_NO_RADIUS
	radius_copy_class(&entry->radius_class, &eapol->radius_class);
#endif /* CONFIG_NO_RADIUS */

	entry->eap_type_authsrv = eapol->eap_type_authsrv;

	vlan_desc = ((struct sta_info *) eapol->sta)->vlan_desc;
	if (vlan_desc && vlan_desc->notempty) {
		entry->vlan_desc = os_zalloc(sizeof(struct vlan_description));
		if (entry->vlan_desc)
			*entry->vlan_desc = *vlan_desc;
	} else {
		entry->vlan_desc = NULL;
	}

	entry->acct_multi_session_id = eapol->acct_multi_session_id;
}