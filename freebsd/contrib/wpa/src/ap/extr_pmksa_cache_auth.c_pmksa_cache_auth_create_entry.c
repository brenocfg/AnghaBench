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
struct rsn_pmksa_cache_entry {size_t pmk_len; int expiration; int akmp; int /*<<< orphan*/  spa; int /*<<< orphan*/  pmkid; int /*<<< orphan*/  pmk; } ;
struct os_reltime {int sec; } ;
struct eapol_state_machine {int dummy; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 size_t PMKID_LEN ; 
 size_t PMK_LEN_MAX ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 ; 
 scalar_t__ dot11RSNAConfigPMKLifetime ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 struct rsn_pmksa_cache_entry* os_zalloc (int) ; 
 int /*<<< orphan*/  pmksa_cache_from_eapol_data (struct rsn_pmksa_cache_entry*,struct eapol_state_machine*) ; 
 int /*<<< orphan*/  rsn_pmkid (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rsn_pmkid_suite_b (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsn_pmkid_suite_b_192 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_suite_b (int) ; 

struct rsn_pmksa_cache_entry *
pmksa_cache_auth_create_entry(const u8 *pmk, size_t pmk_len, const u8 *pmkid,
			      const u8 *kck, size_t kck_len, const u8 *aa,
			      const u8 *spa, int session_timeout,
			      struct eapol_state_machine *eapol, int akmp)
{
	struct rsn_pmksa_cache_entry *entry;
	struct os_reltime now;

	if (pmk_len > PMK_LEN_MAX)
		return NULL;

	if (wpa_key_mgmt_suite_b(akmp) && !kck)
		return NULL;

	entry = os_zalloc(sizeof(*entry));
	if (entry == NULL)
		return NULL;
	os_memcpy(entry->pmk, pmk, pmk_len);
	entry->pmk_len = pmk_len;
	if (pmkid)
		os_memcpy(entry->pmkid, pmkid, PMKID_LEN);
	else if (akmp == WPA_KEY_MGMT_IEEE8021X_SUITE_B_192)
		rsn_pmkid_suite_b_192(kck, kck_len, aa, spa, entry->pmkid);
	else if (wpa_key_mgmt_suite_b(akmp))
		rsn_pmkid_suite_b(kck, kck_len, aa, spa, entry->pmkid);
	else
		rsn_pmkid(pmk, pmk_len, aa, spa, entry->pmkid, akmp);
	os_get_reltime(&now);
	entry->expiration = now.sec;
	if (session_timeout > 0)
		entry->expiration += session_timeout;
	else
		entry->expiration += dot11RSNAConfigPMKLifetime;
	entry->akmp = akmp;
	os_memcpy(entry->spa, spa, ETH_ALEN);
	pmksa_cache_from_eapol_data(entry, eapol);

	return entry;
}