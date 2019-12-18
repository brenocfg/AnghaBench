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
struct bhnd_nvram_store {int data_caps; int /*<<< orphan*/  data; int /*<<< orphan*/ * root_path; } ;
typedef  int /*<<< orphan*/  bhnd_nvstore_name_info ;

/* Variables and functions */
 int BHND_NVRAM_DATA_CAP_DEVPATHS ; 
 int /*<<< orphan*/  BHND_NVSTORE_LOCK_ASSERT (struct bhnd_nvram_store*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_NVSTORE_NAME_INTERNAL ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,char const*,int) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 char* bhnd_nvram_data_next (int /*<<< orphan*/ ,void**) ; 
 int bhnd_nvstore_parse_name_info (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int bhnd_nvstore_var_register_path (struct bhnd_nvram_store*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int
bhnd_nvstore_parse_path_entries(struct bhnd_nvram_store *sc)
{
	const char	*name;
	void		*cookiep;
	int		 error;

	BHND_NVSTORE_LOCK_ASSERT(sc, MA_OWNED);

	/* Skip path registration if the data source does not support device
	 * paths. */
	if (!(sc->data_caps & BHND_NVRAM_DATA_CAP_DEVPATHS)) {
		BHND_NV_ASSERT(sc->root_path != NULL, ("missing root path"));
		return (0);
	}

	/* Otherwise, parse and register all paths and path aliases */
	cookiep = NULL;
	while ((name = bhnd_nvram_data_next(sc->data, &cookiep))) {
		bhnd_nvstore_name_info info;

		/* Parse the name info */
		error = bhnd_nvstore_parse_name_info(name,
		    BHND_NVSTORE_NAME_INTERNAL, sc->data_caps, &info);
		if (error)
			return (error);

		/* Register the path */
		error = bhnd_nvstore_var_register_path(sc, &info, cookiep);
		if (error) {
			BHND_NV_LOG("failed to register path for %s: %d\n",
			    name, error);
			return (error);
		}
	}

	return (0);
}