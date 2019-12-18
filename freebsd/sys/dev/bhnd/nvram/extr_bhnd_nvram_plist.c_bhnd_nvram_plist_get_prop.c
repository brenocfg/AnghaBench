#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bhnd_nvram_prop ;
struct TYPE_3__ {int /*<<< orphan*/ * prop; } ;
typedef  TYPE_1__ bhnd_nvram_plist_entry ;
typedef  int /*<<< orphan*/  bhnd_nvram_plist ;

/* Variables and functions */
 TYPE_1__* bhnd_nvram_plist_get_entry (int /*<<< orphan*/ *,char const*) ; 

bhnd_nvram_prop *
bhnd_nvram_plist_get_prop(bhnd_nvram_plist *plist, const char *name)
{
	bhnd_nvram_plist_entry *entry;

	if ((entry = bhnd_nvram_plist_get_entry(plist, name)) == NULL)
		return (NULL);

	return (entry->prop);
}