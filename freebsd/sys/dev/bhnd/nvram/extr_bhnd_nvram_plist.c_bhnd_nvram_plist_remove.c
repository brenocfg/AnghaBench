#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  prop; } ;
typedef  TYPE_1__ bhnd_nvram_plist_entry ;
struct TYPE_10__ {scalar_t__ num_entries; int /*<<< orphan*/  entries; } ;
typedef  TYPE_2__ bhnd_nvram_plist ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nv_free (TYPE_1__*) ; 
 TYPE_1__* bhnd_nvram_plist_get_entry (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  bhnd_nvram_prop_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl_hash_link ; 
 int /*<<< orphan*/  pl_link ; 

void
bhnd_nvram_plist_remove(bhnd_nvram_plist *plist, const char *name)
{
	bhnd_nvram_plist_entry *entry;

	/* Fetch entry */
	entry = bhnd_nvram_plist_get_entry(plist, name);
	if (entry == NULL)
		return;

	/* Remove from entry list and hash table */
	TAILQ_REMOVE(&plist->entries, entry, pl_link);
	LIST_REMOVE(entry, pl_hash_link);

	/* Free plist entry */
	bhnd_nvram_prop_release(entry->prop);
	bhnd_nv_free(entry);

	/* Decrement entry count */
	BHND_NV_ASSERT(plist->num_entries > 0, ("entry count over-release"));
	plist->num_entries--;
}