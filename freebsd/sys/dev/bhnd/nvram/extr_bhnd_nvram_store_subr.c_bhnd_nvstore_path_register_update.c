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
struct bhnd_nvram_store {int /*<<< orphan*/  data; TYPE_1__* root_path; } ;
struct TYPE_6__ {int /*<<< orphan*/  pending; int /*<<< orphan*/  path_str; } ;
typedef  TYPE_1__ bhnd_nvstore_path ;
struct TYPE_7__ {int /*<<< orphan*/  alias; } ;
typedef  TYPE_2__ bhnd_nvstore_alias ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;

/* Variables and functions */
 scalar_t__ BHND_NVRAM_TYPE_NULL ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,char const*,int) ; 
 int ENOMEM ; 
 int bhnd_nv_asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  bhnd_nv_free (char*) ; 
 int bhnd_nvram_data_filter_setvar (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int bhnd_nvram_data_filter_unsetvar (int /*<<< orphan*/ ,char const*) ; 
 char* bhnd_nvram_data_getvar_name (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  bhnd_nvram_plist_remove (int /*<<< orphan*/ ,char const*) ; 
 int bhnd_nvram_plist_replace_val (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bhnd_nvram_val_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 
 scalar_t__ bhnd_nvram_val_type (int /*<<< orphan*/ *) ; 
 TYPE_2__* bhnd_nvstore_find_alias (struct bhnd_nvram_store*,int /*<<< orphan*/ ) ; 
 void* bhnd_nvstore_path_data_lookup (struct bhnd_nvram_store*,TYPE_1__*,char const*) ; 

int
bhnd_nvstore_path_register_update(struct bhnd_nvram_store *sc,
    bhnd_nvstore_path *path, const char *name, bhnd_nvram_val *value)
{
	bhnd_nvram_val		*prop_val;
	const char		*full_name;
	void			*cookiep;
	char			*namebuf;
	int			 error;
	bool			 nvram_committed;

	namebuf = NULL;
	prop_val = NULL;

	/* Determine whether the variable is currently defined in the
	 * backing NVRAM data, and derive its full path-prefixed name */
	nvram_committed = false;
	cookiep = bhnd_nvstore_path_data_lookup(sc, path, name);
	if (cookiep != NULL) {
		/* Variable is defined in the backing data */
		nvram_committed = true;

		/* Use the existing variable name */
		full_name = bhnd_nvram_data_getvar_name(sc->data, cookiep);
	} else if (path == sc->root_path) {
		/* No prefix required for root path */
		full_name = name;
	} else {
		bhnd_nvstore_alias	*alias;
		int			 len;

		/* New variable is being set; we need to determine the
		 * appropriate path prefix */
		alias = bhnd_nvstore_find_alias(sc, path->path_str);
		if (alias != NULL) {
			/* Use <alias>:name */
			len = bhnd_nv_asprintf(&namebuf, "%lu:%s", alias->alias,
			    name);
		} else {
			/* Use path/name */
			len = bhnd_nv_asprintf(&namebuf, "%s/%s",
			    path->path_str, name);
		}

		if (len < 0)
			return (ENOMEM);

		full_name = namebuf;
	}

	/* Allow the data store to filter the NVRAM operation */
	if (bhnd_nvram_val_type(value) == BHND_NVRAM_TYPE_NULL) {
		error = bhnd_nvram_data_filter_unsetvar(sc->data, full_name);
		if (error) {
			BHND_NV_LOG("cannot unset property %s: %d\n", full_name,
			    error);
			goto cleanup;
		}

		if ((prop_val = bhnd_nvram_val_copy(value)) == NULL) {
			error = ENOMEM;
			goto cleanup;
		}
	} else {
		error = bhnd_nvram_data_filter_setvar(sc->data, full_name,
		    value,  &prop_val);
		if (error) {
			BHND_NV_LOG("cannot set property %s: %d\n", full_name,
			    error);
			goto cleanup;
		}
	}

	/* Add relative variable name to the per-path update list */
	if (bhnd_nvram_val_type(value) == BHND_NVRAM_TYPE_NULL &&
	    !nvram_committed)
	{
		/* This is a deletion request for a variable not defined in
		 * out backing store; we can simply remove the corresponding
		 * update entry. */
		bhnd_nvram_plist_remove(path->pending, name);
	} else {
		/* Update or append a pending update entry */
		error = bhnd_nvram_plist_replace_val(path->pending, name,
		    prop_val);
		if (error)
			goto cleanup;
	}

	/* Success */
	error = 0;

cleanup:
	if (namebuf != NULL)
		bhnd_nv_free(namebuf);

	if (prop_val != NULL)
		bhnd_nvram_val_release(prop_val);

	return (error);
}