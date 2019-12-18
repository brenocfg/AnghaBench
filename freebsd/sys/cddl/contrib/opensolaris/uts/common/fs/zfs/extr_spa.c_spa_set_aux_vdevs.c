#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
struct TYPE_3__ {int /*<<< orphan*/ * sav_config; } ;
typedef  TYPE_1__ spa_aux_vdev_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_TYPE_NVLIST_ARRAY ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/ ** kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ **,int) ; 
 scalar_t__ nvlist_add_nvlist_array (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **,int) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ***,int*) ; 
 scalar_t__ nvlist_remove (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_set_aux_vdevs(spa_aux_vdev_t *sav, nvlist_t **devs, int ndevs,
    const char *config)
{
	int i;

	if (sav->sav_config != NULL) {
		nvlist_t **olddevs;
		uint_t oldndevs;
		nvlist_t **newdevs;

		/*
		 * Generate new dev list by concatentating with the
		 * current dev list.
		 */
		VERIFY(nvlist_lookup_nvlist_array(sav->sav_config, config,
		    &olddevs, &oldndevs) == 0);

		newdevs = kmem_alloc(sizeof (void *) *
		    (ndevs + oldndevs), KM_SLEEP);
		for (i = 0; i < oldndevs; i++)
			VERIFY(nvlist_dup(olddevs[i], &newdevs[i],
			    KM_SLEEP) == 0);
		for (i = 0; i < ndevs; i++)
			VERIFY(nvlist_dup(devs[i], &newdevs[i + oldndevs],
			    KM_SLEEP) == 0);

		VERIFY(nvlist_remove(sav->sav_config, config,
		    DATA_TYPE_NVLIST_ARRAY) == 0);

		VERIFY(nvlist_add_nvlist_array(sav->sav_config,
		    config, newdevs, ndevs + oldndevs) == 0);
		for (i = 0; i < oldndevs + ndevs; i++)
			nvlist_free(newdevs[i]);
		kmem_free(newdevs, (oldndevs + ndevs) * sizeof (void *));
	} else {
		/*
		 * Generate a new dev list.
		 */
		VERIFY(nvlist_alloc(&sav->sav_config, NV_UNIQUE_NAME,
		    KM_SLEEP) == 0);
		VERIFY(nvlist_add_nvlist_array(sav->sav_config, config,
		    devs, ndevs) == 0);
	}
}