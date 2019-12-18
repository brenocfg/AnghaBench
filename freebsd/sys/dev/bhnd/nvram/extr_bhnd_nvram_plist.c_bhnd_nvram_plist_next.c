#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bhnd_nvram_prop ;
struct TYPE_13__ {TYPE_1__* prop; } ;
typedef  TYPE_2__ bhnd_nvram_plist_entry ;
struct TYPE_14__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_3__ bhnd_nvram_plist ;

/* Variables and functions */
 TYPE_2__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_2__* TAILQ_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* bhnd_nvram_plist_get_entry (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl_link ; 

bhnd_nvram_prop *
bhnd_nvram_plist_next(bhnd_nvram_plist *plist, bhnd_nvram_prop *prop)
{
	bhnd_nvram_plist_entry *entry;

	if (prop == NULL) {
		if ((entry = TAILQ_FIRST(&plist->entries)) == NULL)
			return (NULL);

		return (entry->prop);
	}

	/* Look up previous property entry by name */
	if ((entry = bhnd_nvram_plist_get_entry(plist, prop->name)) == NULL)
		return (NULL);

	/* The property instance must be identical */
	if (entry->prop != prop)
		return (NULL);

	/* Fetch next entry */
	if ((entry = TAILQ_NEXT(entry, pl_link)) == NULL)
		return (NULL);

	return (entry->prop);
}