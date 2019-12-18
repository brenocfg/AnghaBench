#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bhnd_nvram_prop ;
struct TYPE_8__ {int /*<<< orphan*/  prop; } ;
typedef  TYPE_2__ bhnd_nvram_plist_entry ;
typedef  int /*<<< orphan*/  bhnd_nvram_plist ;

/* Variables and functions */
 int bhnd_nvram_plist_append (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* bhnd_nvram_plist_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_prop_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_prop_retain (TYPE_1__*) ; 

int
bhnd_nvram_plist_replace(bhnd_nvram_plist *plist, bhnd_nvram_prop *prop)
{
	bhnd_nvram_plist_entry	*entry;

	/* Fetch current entry */
	entry = bhnd_nvram_plist_get_entry(plist, prop->name);
	if (entry == NULL) {
		/* Not found -- append property instead */
		return (bhnd_nvram_plist_append(plist, prop));
	}

	/* Replace the current entry's property reference */
	bhnd_nvram_prop_release(entry->prop);
	entry->prop = bhnd_nvram_prop_retain(prop);

	return (0);
}