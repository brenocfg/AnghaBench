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
struct rsn_pmksa_cache_entry {struct rsn_pmksa_cache_entry* next; } ;
struct rsn_pmksa_cache {int /*<<< orphan*/ ** pmkid; struct rsn_pmksa_cache_entry* pmksa; scalar_t__ pmksa_count; } ;

/* Variables and functions */
 int PMKID_HASH_SIZE ; 
 int /*<<< orphan*/  _pmksa_cache_free_entry (struct rsn_pmksa_cache_entry*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct rsn_pmksa_cache*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct rsn_pmksa_cache*) ; 
 int /*<<< orphan*/  pmksa_cache_expire ; 

void pmksa_cache_auth_deinit(struct rsn_pmksa_cache *pmksa)
{
	struct rsn_pmksa_cache_entry *entry, *prev;
	int i;

	if (pmksa == NULL)
		return;

	entry = pmksa->pmksa;
	while (entry) {
		prev = entry;
		entry = entry->next;
		_pmksa_cache_free_entry(prev);
	}
	eloop_cancel_timeout(pmksa_cache_expire, pmksa, NULL);
	pmksa->pmksa_count = 0;
	pmksa->pmksa = NULL;
	for (i = 0; i < PMKID_HASH_SIZE; i++)
		pmksa->pmkid[i] = NULL;
	os_free(pmksa);
}