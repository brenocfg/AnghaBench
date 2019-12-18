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
typedef  int /*<<< orphan*/  u_long ;
struct bhnd_nvram_store {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  path_str; } ;
typedef  TYPE_1__ bhnd_nvstore_path ;
struct TYPE_6__ {int /*<<< orphan*/  alias; } ;
typedef  TYPE_2__ bhnd_nvstore_alias ;
typedef  int /*<<< orphan*/  bhnd_nvram_plist ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  bhnd_nv_asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nv_free (char*) ; 
 int bhnd_nvram_plist_append_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  bhnd_nvram_plist_contains (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* bhnd_nvstore_find_alias (struct bhnd_nvram_store*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bhnd_nvstore_get_alias (struct bhnd_nvram_store*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_nvstore_export_devpath_alias(struct bhnd_nvram_store *sc,
    bhnd_nvstore_path *path, const char *devpath, bhnd_nvram_plist *plist,
    u_long *alias_val)
{
	bhnd_nvstore_alias	*alias;
	char			*pathvar;
	int			 error;

	*alias_val = 0;

	/* Prefer alias value already reserved for this path. */
	alias = bhnd_nvstore_find_alias(sc, path->path_str);
	if (alias != NULL) {
		*alias_val = alias->alias;

		/* Allocate devpathXX variable name */
		bhnd_nv_asprintf(&pathvar, "devpath%lu", *alias_val);
		if (pathvar == NULL)
			return (ENOMEM);

		/* Append alias variable to property list */
		error = bhnd_nvram_plist_append_string(plist, pathvar, devpath);

		BHND_NV_ASSERT(error != EEXIST, ("reserved alias %lu:%s in use",
		   * alias_val, path->path_str));

		bhnd_nv_free(pathvar);
		return (error);
	}

	/* Find the next free devpathXX alias entry */
	while (1) {
		/* Skip existing reserved alias values */
		while (bhnd_nvstore_get_alias(sc, *alias_val) != NULL) {
			if (*alias_val == ULONG_MAX)
				return (ENOMEM);

			(*alias_val)++;
		}

		/* Allocate devpathXX variable name */
		bhnd_nv_asprintf(&pathvar, "devpath%lu", *alias_val);
		if (pathvar == NULL)
			return (ENOMEM);

		/* If not in-use, we can terminate the search */
		if (!bhnd_nvram_plist_contains(plist, pathvar))
			break;

		/* Keep searching */
		bhnd_nv_free(pathvar);

		if (*alias_val == ULONG_MAX)
			return (ENOMEM);

		(*alias_val)++;
	}

	/* Append alias variable to property list */
	error = bhnd_nvram_plist_append_string(plist, pathvar, devpath);

	bhnd_nv_free(pathvar);
	return (error);
}