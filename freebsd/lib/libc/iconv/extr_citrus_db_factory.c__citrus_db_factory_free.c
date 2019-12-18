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
struct _citrus_db_factory_entry {int /*<<< orphan*/  de_data; scalar_t__ de_data_free; int /*<<< orphan*/  de_key; scalar_t__ de_key_free; int /*<<< orphan*/  df_entries; } ;
struct _citrus_db_factory {int /*<<< orphan*/  de_data; scalar_t__ de_data_free; int /*<<< orphan*/  de_key; scalar_t__ de_key_free; int /*<<< orphan*/  df_entries; } ;

/* Variables and functions */
 struct _citrus_db_factory_entry* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct _citrus_db_factory_entry* _region_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  de_entry ; 
 int /*<<< orphan*/  free (struct _citrus_db_factory_entry*) ; 

void
_citrus_db_factory_free(struct _citrus_db_factory *df)
{
	struct _citrus_db_factory_entry *de;

	while ((de = STAILQ_FIRST(&df->df_entries)) != NULL) {
		STAILQ_REMOVE_HEAD(&df->df_entries, de_entry);
		if (de->de_key_free)
			free(_region_head(&de->de_key));
		if (de->de_data_free)
			free(_region_head(&de->de_data));
		free(de);
	}
	free(df);
}