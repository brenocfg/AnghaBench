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
struct rsn_pmksa_cache {struct rsn_pmksa_cache_entry* pmksa; } ;
struct radius_das_attrs {scalar_t__ acct_session_id; } ;

/* Variables and functions */
 scalar_t__ das_attr_match (struct rsn_pmksa_cache_entry*,struct radius_das_attrs*) ; 
 int /*<<< orphan*/  pmksa_cache_free_entry (struct rsn_pmksa_cache*,struct rsn_pmksa_cache_entry*) ; 

int pmksa_cache_auth_radius_das_disconnect(struct rsn_pmksa_cache *pmksa,
					   struct radius_das_attrs *attr)
{
	int found = 0;
	struct rsn_pmksa_cache_entry *entry, *prev;

	if (attr->acct_session_id)
		return -1;

	entry = pmksa->pmksa;
	while (entry) {
		if (das_attr_match(entry, attr)) {
			found++;
			prev = entry;
			entry = entry->next;
			pmksa_cache_free_entry(pmksa, prev);
			continue;
		}
		entry = entry->next;
	}

	return found ? 0 : -1;
}