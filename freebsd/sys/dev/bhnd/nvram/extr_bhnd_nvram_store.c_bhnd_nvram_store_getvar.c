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
struct bhnd_nvram_store {int /*<<< orphan*/  data; int /*<<< orphan*/  data_caps; } ;
typedef  int /*<<< orphan*/  bhnd_nvstore_path ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bhnd_nvstore_name_info ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;
typedef  int /*<<< orphan*/  bhnd_nvram_prop ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVSTORE_LOCK (struct bhnd_nvram_store*) ; 
 int /*<<< orphan*/  BHND_NVSTORE_NAME_EXTERNAL ; 
 int /*<<< orphan*/  BHND_NVSTORE_UNLOCK (struct bhnd_nvram_store*) ; 
 int ENOENT ; 
 int bhnd_nvram_data_getvar (int /*<<< orphan*/ ,void*,void*,size_t*,int /*<<< orphan*/ ) ; 
 int bhnd_nvram_prop_encode (int /*<<< orphan*/ *,void*,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ bhnd_nvram_prop_is_null (int /*<<< orphan*/ *) ; 
 int bhnd_nvstore_parse_name_info (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* bhnd_nvstore_path_data_lookup (struct bhnd_nvram_store*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bhnd_nvstore_path_get_update (struct bhnd_nvram_store*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bhnd_nvstore_var_get_path (struct bhnd_nvram_store*,TYPE_1__*) ; 

int
bhnd_nvram_store_getvar(struct bhnd_nvram_store *sc, const char *name,
    void *outp, size_t *olen, bhnd_nvram_type otype)
{
	bhnd_nvstore_name_info	 info;
	bhnd_nvstore_path	*path;
	bhnd_nvram_prop		*prop;
	void			*cookiep;
	int			 error;

	BHND_NVSTORE_LOCK(sc);

	/* Parse the variable name */
	error = bhnd_nvstore_parse_name_info(name, BHND_NVSTORE_NAME_EXTERNAL,
	    sc->data_caps, &info);
	if (error)
		goto finished;

	/* Fetch the variable's enclosing path entry */
	if ((path = bhnd_nvstore_var_get_path(sc, &info)) == NULL) {
		error = ENOENT;
		goto finished;
	}

	/* Search uncommitted updates first */
	prop = bhnd_nvstore_path_get_update(sc, path, info.name);
	if (prop != NULL) {
		if (bhnd_nvram_prop_is_null(prop)) {
			/* NULL denotes a pending deletion */
			error = ENOENT;
		} else {
			error = bhnd_nvram_prop_encode(prop, outp, olen, otype);
		}
		goto finished;
	}

	/* Search the backing NVRAM data */
	cookiep = bhnd_nvstore_path_data_lookup(sc, path, info.name);
	if (cookiep != NULL) {
		/* Found in backing store */
		error = bhnd_nvram_data_getvar(sc->data, cookiep, outp, olen,
		     otype);
		goto finished;
	}

	/* Not found */
	error = ENOENT;

finished:
	BHND_NVSTORE_UNLOCK(sc);
	return (error);
}