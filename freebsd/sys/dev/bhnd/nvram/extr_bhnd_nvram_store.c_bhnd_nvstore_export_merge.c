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
typedef  int /*<<< orphan*/  uint32_t ;
struct bhnd_nvram_store {int data_caps; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pending; } ;
typedef  TYPE_1__ bhnd_nvstore_path ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
typedef  int /*<<< orphan*/  bhnd_nvram_prop ;
typedef  int /*<<< orphan*/  bhnd_nvram_plist ;

/* Variables and functions */
 int BHND_NVRAM_DATA_CAP_DEVPATHS ; 
 scalar_t__ BHND_NVSTORE_GET_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPORT_COMMITTED ; 
 int /*<<< orphan*/  EXPORT_DELETED ; 
 int /*<<< orphan*/  EXPORT_UNCOMMITTED ; 
 int bhnd_nvram_data_copy_val (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 
 char* bhnd_nvram_data_getvar_name (int /*<<< orphan*/ ,void*) ; 
 int bhnd_nvram_plist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_plist_append_val (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ bhnd_nvram_plist_contains (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * bhnd_nvram_plist_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bhnd_nvram_prop_is_null (int /*<<< orphan*/ *) ; 
 char* bhnd_nvram_trim_path_name (char const*) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 
 void* bhnd_nvstore_path_data_next (struct bhnd_nvram_store*,TYPE_1__*,void**) ; 

__attribute__((used)) static int
bhnd_nvstore_export_merge(struct bhnd_nvram_store *sc,
    bhnd_nvstore_path *path, bhnd_nvram_plist *merged, uint32_t flags)
{
	void	*cookiep, *idxp;
	int	 error;

	/* Populate merged list with all pending variables */
	if (BHND_NVSTORE_GET_FLAG(flags, EXPORT_UNCOMMITTED)) {
		bhnd_nvram_prop *prop;

		prop = NULL;
		while ((prop = bhnd_nvram_plist_next(path->pending, prop))) {
			/* Skip variables marked for deletion */
			if (!BHND_NVSTORE_GET_FLAG(flags, EXPORT_DELETED)) {
				if (bhnd_nvram_prop_is_null(prop))
					continue;
			}

			/* Append to merged list */
			error = bhnd_nvram_plist_append(merged, prop);
			if (error)
				return (error);
		}
	}

	/* Skip merging committed variables? */
	if (!BHND_NVSTORE_GET_FLAG(flags, EXPORT_COMMITTED))
		return (0);

	/* Merge in the committed NVRAM variables */
	idxp = NULL;
	while ((cookiep = bhnd_nvstore_path_data_next(sc, path, &idxp))) {
		const char	*name;
		bhnd_nvram_val	*val;

		/* Fetch the variable name */
		name = bhnd_nvram_data_getvar_name(sc->data, cookiep);

		/* Trim device path prefix */
		if (sc->data_caps & BHND_NVRAM_DATA_CAP_DEVPATHS)
			name = bhnd_nvram_trim_path_name(name);

		/* Skip if already defined in pending updates */
		if (BHND_NVSTORE_GET_FLAG(flags, EXPORT_UNCOMMITTED)) {
			if (bhnd_nvram_plist_contains(path->pending, name))
				continue;
		}

		/* Skip if higher precedence value was already defined. This
		 * may occur if the underlying data store contains duplicate
		 * keys; iteration will always return the definition with
		 * the highest precedence first */
		if (bhnd_nvram_plist_contains(merged, name))
			continue;

		/* Fetch the variable's value representation */
		if ((error = bhnd_nvram_data_copy_val(sc->data, cookiep, &val)))
			return (error);

		/* Add to path variable list */
		error = bhnd_nvram_plist_append_val(merged, name, val);
		bhnd_nvram_val_release(val);
		if (error)
			return (error);
	}

	return (0);
}