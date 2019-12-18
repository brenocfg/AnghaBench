#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* archives; struct TYPE_6__* next; int /*<<< orphan*/  lang; } ;
typedef  TYPE_1__ lmo_catalog_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ lmo_archive_t ;

/* Variables and functions */
 TYPE_1__* _lmo_catalogs ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  lmo_close (TYPE_2__*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

void lmo_close_catalog(const char *lang)
{
	lmo_archive_t *ar, *next;
	lmo_catalog_t *cat, *prev;

	for (prev = NULL, cat = _lmo_catalogs; cat; prev = cat, cat = cat->next)
	{
		if (!strncmp(cat->lang, lang, sizeof(cat->lang)))
		{
			if (prev)
				prev->next = cat->next;
			else
				_lmo_catalogs = cat->next;

			for (ar = cat->archives; ar; ar = next)
			{
				next = ar->next;
				lmo_close(ar);
			}

			free(cat);
			break;
		}
	}
}