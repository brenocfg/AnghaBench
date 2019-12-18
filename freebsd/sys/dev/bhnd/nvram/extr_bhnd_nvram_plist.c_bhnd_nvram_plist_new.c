#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int refs; int /*<<< orphan*/ * names; int /*<<< orphan*/  entries; scalar_t__ num_entries; } ;
typedef  TYPE_1__ bhnd_nvram_plist ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* bhnd_nv_calloc (int,int) ; 
 size_t nitems (int /*<<< orphan*/ *) ; 

bhnd_nvram_plist *
bhnd_nvram_plist_new(void)
{
	bhnd_nvram_plist *plist;

	plist = bhnd_nv_calloc(1, sizeof(*plist));
	if (plist == NULL)
		return NULL;

	/* Implicit caller-owned reference */
	plist->refs = 1;

	/* Initialize entry list */
	plist->num_entries = 0;
	TAILQ_INIT(&plist->entries);

	/* Initialize entry hash table */
	for (size_t i = 0; i < nitems(plist->names); i++)
		LIST_INIT(&plist->names[i]);

	return (plist);
}