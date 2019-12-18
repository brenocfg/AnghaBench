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
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  spa_import_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int EAGAIN ; 
 int spa_ld_mos_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_ld_prepare_for_reload (int /*<<< orphan*/ *) ; 
 int spa_ld_trusted_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_load_note (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
spa_ld_mos_with_trusted_config(spa_t *spa, spa_import_type_t type,
    boolean_t *update_config_cache)
{
	int error;

	/*
	 * Parse the config for pool, open and validate vdevs,
	 * select an uberblock, and use that uberblock to open
	 * the MOS.
	 */
	error = spa_ld_mos_init(spa, type);
	if (error != 0)
		return (error);

	/*
	 * Retrieve the trusted config stored in the MOS and use it to create
	 * a new, exact version of the vdev tree, then reopen all vdevs.
	 */
	error = spa_ld_trusted_config(spa, type, B_FALSE);
	if (error == EAGAIN) {
		if (update_config_cache != NULL)
			*update_config_cache = B_TRUE;

		/*
		 * Redo the loading process with the trusted config if it is
		 * too different from the untrusted config.
		 */
		spa_ld_prepare_for_reload(spa);
		spa_load_note(spa, "RELOADING");
		error = spa_ld_mos_init(spa, type);
		if (error != 0)
			return (error);

		error = spa_ld_trusted_config(spa, type, B_TRUE);
		if (error != 0)
			return (error);

	} else if (error != 0) {
		return (error);
	}

	return (0);
}