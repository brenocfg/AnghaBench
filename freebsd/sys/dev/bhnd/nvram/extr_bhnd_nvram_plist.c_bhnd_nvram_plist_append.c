#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bhnd_nvram_prop ;
typedef  int /*<<< orphan*/  bhnd_nvram_plist_entry_list ;
struct TYPE_12__ {int /*<<< orphan*/  prop; } ;
typedef  TYPE_2__ bhnd_nvram_plist_entry ;
struct TYPE_13__ {scalar_t__ num_entries; int /*<<< orphan*/ * names; int /*<<< orphan*/  entries; } ;
typedef  TYPE_3__ bhnd_nvram_plist ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HASHINIT ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* bhnd_nv_malloc (int) ; 
 scalar_t__ bhnd_nvram_plist_contains (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_prop_retain (TYPE_1__*) ; 
 size_t hash32_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pl_hash_link ; 
 int /*<<< orphan*/  pl_link ; 

int
bhnd_nvram_plist_append(bhnd_nvram_plist *plist, bhnd_nvram_prop *prop)
{
	bhnd_nvram_plist_entry_list	*hash_list;
	bhnd_nvram_plist_entry 		*entry;
	uint32_t			 h;

	if (bhnd_nvram_plist_contains(plist, prop->name))
		return (EEXIST);

	/* Have we hit the maximum representable entry count? */
	if (plist->num_entries == SIZE_MAX)
		return (ENOMEM);

	/* Allocate new entry */
	entry = bhnd_nv_malloc(sizeof(*entry));
	if (entry == NULL)
		return (ENOMEM);

	entry->prop = bhnd_nvram_prop_retain(prop);

	/* Append to entry list */
	TAILQ_INSERT_TAIL(&plist->entries, entry, pl_link);

	/* Add to name-based hash table */
	h = hash32_str(prop->name, HASHINIT);
	hash_list = &plist->names[h % nitems(plist->names)];
	LIST_INSERT_HEAD(hash_list, entry, pl_hash_link);

	/* Increment entry count */
	plist->num_entries++;

	return (0);
}