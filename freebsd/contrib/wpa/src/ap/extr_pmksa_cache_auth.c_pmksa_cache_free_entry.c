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
struct rsn_pmksa_cache_entry {struct rsn_pmksa_cache_entry* next; struct rsn_pmksa_cache_entry* hnext; int /*<<< orphan*/  pmkid; } ;
struct rsn_pmksa_cache {struct rsn_pmksa_cache_entry* pmksa; struct rsn_pmksa_cache_entry** pmkid; int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* free_cb ) (struct rsn_pmksa_cache_entry*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pmksa_count; } ;

/* Variables and functions */
 unsigned int PMKID_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pmksa_cache_free_entry (struct rsn_pmksa_cache_entry*) ; 
 int /*<<< orphan*/  stub1 (struct rsn_pmksa_cache_entry*,int /*<<< orphan*/ ) ; 

void pmksa_cache_free_entry(struct rsn_pmksa_cache *pmksa,
			    struct rsn_pmksa_cache_entry *entry)
{
	struct rsn_pmksa_cache_entry *pos, *prev;
	unsigned int hash;

	pmksa->pmksa_count--;
	pmksa->free_cb(entry, pmksa->ctx);

	/* unlink from hash list */
	hash = PMKID_HASH(entry->pmkid);
	pos = pmksa->pmkid[hash];
	prev = NULL;
	while (pos) {
		if (pos == entry) {
			if (prev != NULL)
				prev->hnext = entry->hnext;
			else
				pmksa->pmkid[hash] = entry->hnext;
			break;
		}
		prev = pos;
		pos = pos->hnext;
	}

	/* unlink from entry list */
	pos = pmksa->pmksa;
	prev = NULL;
	while (pos) {
		if (pos == entry) {
			if (prev != NULL)
				prev->next = entry->next;
			else
				pmksa->pmksa = entry->next;
			break;
		}
		prev = pos;
		pos = pos->next;
	}

	_pmksa_cache_free_entry(entry);
}