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
struct bhnd_nvram_store {int /*<<< orphan*/  data_caps; } ;
typedef  int /*<<< orphan*/  bhnd_nvstore_path ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bhnd_nvstore_name_info ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVSTORE_LOCK_ASSERT (struct bhnd_nvram_store*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_NVSTORE_NAME_EXTERNAL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int bhnd_nvstore_parse_name_info (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int bhnd_nvstore_path_register_update (struct bhnd_nvram_store*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bhnd_nvstore_var_get_path (struct bhnd_nvram_store*,TYPE_1__*) ; 

__attribute__((used)) static int
bhnd_nvram_store_setval_common(struct bhnd_nvram_store *sc, const char *name,
    bhnd_nvram_val *value)
{
	bhnd_nvstore_path	*path;
	bhnd_nvstore_name_info	 info;
	int			 error;

	BHND_NVSTORE_LOCK_ASSERT(sc, MA_OWNED);

	/* Parse the variable name */
	error = bhnd_nvstore_parse_name_info(name, BHND_NVSTORE_NAME_EXTERNAL,
	    sc->data_caps, &info);
	if (error)
		return (error);

	/* Fetch the variable's enclosing path entry */
	if ((path = bhnd_nvstore_var_get_path(sc, &info)) == NULL)
		return (error);

	/* Register the update entry */
	return (bhnd_nvstore_path_register_update(sc, path, info.name, value));
}