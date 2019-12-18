#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bhnd_nvram_store {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__* index; int /*<<< orphan*/  path_str; } ;
typedef  TYPE_2__ bhnd_nvstore_path ;
struct TYPE_5__ {scalar_t__ count; void** cookiep; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVSTORE_LOCK_ASSERT (struct bhnd_nvram_store*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/ * bhnd_nvram_data_next (int /*<<< orphan*/ ,void**) ; 
 int bhnd_nvstore_is_root_path (struct bhnd_nvram_store*,TYPE_2__*) ; 

void *
bhnd_nvstore_path_data_next(struct bhnd_nvram_store *sc,
     bhnd_nvstore_path *path, void **indexp)
{
	void **index_ref;

	BHND_NVSTORE_LOCK_ASSERT(sc, MA_OWNED);

	/* No index */
	if (path->index == NULL) {
		/* An index is required for all non-empty, non-root path
		 * instances */
		BHND_NV_ASSERT(bhnd_nvstore_is_root_path(sc, path),
		    ("missing index for non-root path %s", path->path_str));

		/* Iterate NVRAM data directly, using the NVRAM data's cookiep
		 * value as our indexp context */
		if ((bhnd_nvram_data_next(sc->data, indexp)) == NULL)
			return (NULL);

		return (*indexp);
	}

	/* Empty index */
	if (path->index->count == 0)
		return (NULL);

	if (*indexp == NULL) {
		/* First index entry */
		index_ref = &path->index->cookiep[0];
	} else {
		size_t idxpos;

		/* Advance to next index entry */
		index_ref = *indexp;
		index_ref++;

		/* Hit end of index? */
		BHND_NV_ASSERT(index_ref > path->index->cookiep,
		    ("invalid indexp"));

		idxpos = (index_ref - path->index->cookiep);
		if (idxpos >= path->index->count)
			return (NULL);
	}

	/* Provide new index position */
	*indexp = index_ref;

	/* Return the data's cookiep value */
	return (*index_ref);
}