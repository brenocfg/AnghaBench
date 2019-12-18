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
struct TYPE_4__ {int /*<<< orphan*/  lang; struct TYPE_4__* next; } ;
typedef  TYPE_1__ lmo_catalog_t ;

/* Variables and functions */
 TYPE_1__* _lmo_active_catalog ; 
 TYPE_1__* _lmo_catalogs ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

int lmo_change_catalog(const char *lang)
{
	lmo_catalog_t *cat;

	for (cat = _lmo_catalogs; cat; cat = cat->next)
	{
		if (!strncmp(cat->lang, lang, sizeof(cat->lang)))
		{
			_lmo_active_catalog = cat;
			return 0;
		}
	}

	return -1;
}