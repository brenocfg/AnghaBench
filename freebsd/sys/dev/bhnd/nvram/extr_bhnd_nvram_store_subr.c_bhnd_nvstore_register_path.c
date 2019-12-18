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
typedef  size_t uint32_t ;
struct bhnd_nvram_store {scalar_t__ num_paths; int /*<<< orphan*/ * paths; } ;
typedef  int /*<<< orphan*/  bhnd_nvstore_path_list ;
struct TYPE_4__ {int /*<<< orphan*/  path_str; } ;
typedef  TYPE_1__ bhnd_nvstore_path ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVSTORE_LOCK_ASSERT (struct bhnd_nvram_store*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HASHINIT ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/ * bhnd_nvstore_get_path (struct bhnd_nvram_store*,char const*,size_t) ; 
 TYPE_1__* bhnd_nvstore_path_new (char const*,size_t) ; 
 size_t hash32_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  np_link ; 

int
bhnd_nvstore_register_path(struct bhnd_nvram_store *sc, const char *path_str,
    size_t path_len)
{
	bhnd_nvstore_path_list	*plist;
	bhnd_nvstore_path	*path;
	uint32_t		 h;

	BHND_NVSTORE_LOCK_ASSERT(sc, MA_OWNED);

	/* Already exists? */
	if (bhnd_nvstore_get_path(sc, path_str, path_len) != NULL)
		return (0);

	/* Can't represent more than SIZE_MAX paths */
	if (sc->num_paths == SIZE_MAX)
		return (ENOMEM);

	/* Allocate new entry */
	path = bhnd_nvstore_path_new(path_str, path_len);
	if (path == NULL)
		return (ENOMEM);

	/* Insert in path hash table */
	h = hash32_str(path->path_str, HASHINIT);
	plist = &sc->paths[h % nitems(sc->paths)];
	LIST_INSERT_HEAD(plist, path, np_link);

	/* Increment path count */
	sc->num_paths++;

	return (0);
}