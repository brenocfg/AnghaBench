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
struct bhnd_nvram_store {int /*<<< orphan*/  root_path; int /*<<< orphan*/ * data_opts; int /*<<< orphan*/  data_caps; int /*<<< orphan*/  data; int /*<<< orphan*/ * aliases; scalar_t__ num_aliases; int /*<<< orphan*/ * paths; scalar_t__ num_paths; } ;
struct bhnd_nvram_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVSTORE_LOCK (struct bhnd_nvram_store*) ; 
 int /*<<< orphan*/  BHND_NVSTORE_LOCK_INIT (struct bhnd_nvram_store*) ; 
 int /*<<< orphan*/  BHND_NVSTORE_ROOT_PATH ; 
 int /*<<< orphan*/  BHND_NVSTORE_ROOT_PATH_LEN ; 
 int /*<<< orphan*/  BHND_NVSTORE_UNLOCK (struct bhnd_nvram_store*) ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 struct bhnd_nvram_store* bhnd_nv_calloc (int,int) ; 
 int /*<<< orphan*/  bhnd_nvram_data_caps (struct bhnd_nvram_data*) ; 
 int /*<<< orphan*/ * bhnd_nvram_data_options (struct bhnd_nvram_data*) ; 
 int /*<<< orphan*/  bhnd_nvram_data_retain (struct bhnd_nvram_data*) ; 
 int /*<<< orphan*/ * bhnd_nvram_plist_new () ; 
 int /*<<< orphan*/  bhnd_nvram_plist_retain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_store_free (struct bhnd_nvram_store*) ; 
 int /*<<< orphan*/  bhnd_nvstore_get_path (struct bhnd_nvram_store*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bhnd_nvstore_parse_data (struct bhnd_nvram_store*) ; 
 int bhnd_nvstore_register_path (struct bhnd_nvram_store*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t nitems (int /*<<< orphan*/ *) ; 

int
bhnd_nvram_store_new(struct bhnd_nvram_store **store,
    struct bhnd_nvram_data *data)
{
	struct bhnd_nvram_store *sc;
	int			 error;

	/* Allocate new instance */
	sc = bhnd_nv_calloc(1, sizeof(*sc));
	if (sc == NULL)
		return (ENOMEM);

	BHND_NVSTORE_LOCK_INIT(sc);
	BHND_NVSTORE_LOCK(sc);

	/* Initialize path hash table */
	sc->num_paths = 0;
	for (size_t i = 0; i < nitems(sc->paths); i++)
		LIST_INIT(&sc->paths[i]);

	/* Initialize alias hash table */
	sc->num_aliases = 0;
	for (size_t i = 0; i < nitems(sc->aliases); i++)
		LIST_INIT(&sc->aliases[i]);

	/* Retain the NVRAM data */
	sc->data = bhnd_nvram_data_retain(data);
	sc->data_caps = bhnd_nvram_data_caps(data);
	sc->data_opts = bhnd_nvram_data_options(data);
	if (sc->data_opts != NULL) {
		bhnd_nvram_plist_retain(sc->data_opts);
	} else {
		sc->data_opts = bhnd_nvram_plist_new();
		if (sc->data_opts == NULL) {
			error = ENOMEM;
			goto cleanup;
		}
	}

	/* Register required root path */
	error = bhnd_nvstore_register_path(sc, BHND_NVSTORE_ROOT_PATH,
	    BHND_NVSTORE_ROOT_PATH_LEN);
	if (error)
		goto cleanup;

	sc->root_path = bhnd_nvstore_get_path(sc, BHND_NVSTORE_ROOT_PATH,
	    BHND_NVSTORE_ROOT_PATH_LEN);
	BHND_NV_ASSERT(sc->root_path, ("missing root path"));

	/* Parse all variables vended by our backing NVRAM data instance,
	 * generating all path entries, alias entries, and variable indexes */
	if ((error = bhnd_nvstore_parse_data(sc)))
		goto cleanup;

	*store = sc;

	BHND_NVSTORE_UNLOCK(sc);
	return (0);

cleanup:
	BHND_NVSTORE_UNLOCK(sc);
	bhnd_nvram_store_free(sc);
	return (error);
}