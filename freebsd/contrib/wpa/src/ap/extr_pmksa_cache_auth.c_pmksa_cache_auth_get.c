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
struct rsn_pmksa_cache_entry {int /*<<< orphan*/  spa; struct rsn_pmksa_cache_entry* next; int /*<<< orphan*/  pmkid; struct rsn_pmksa_cache_entry* hnext; } ;
struct rsn_pmksa_cache {struct rsn_pmksa_cache_entry* pmksa; struct rsn_pmksa_cache_entry** pmkid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 size_t PMKID_HASH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PMKID_LEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

struct rsn_pmksa_cache_entry *
pmksa_cache_auth_get(struct rsn_pmksa_cache *pmksa,
		     const u8 *spa, const u8 *pmkid)
{
	struct rsn_pmksa_cache_entry *entry;

	if (pmkid) {
		for (entry = pmksa->pmkid[PMKID_HASH(pmkid)]; entry;
		     entry = entry->hnext) {
			if ((spa == NULL ||
			     os_memcmp(entry->spa, spa, ETH_ALEN) == 0) &&
			    os_memcmp(entry->pmkid, pmkid, PMKID_LEN) == 0)
				return entry;
		}
	} else {
		for (entry = pmksa->pmksa; entry; entry = entry->next) {
			if (spa == NULL ||
			    os_memcmp(entry->spa, spa, ETH_ALEN) == 0)
				return entry;
		}
	}

	return NULL;
}