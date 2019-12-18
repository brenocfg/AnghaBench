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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_TYPE_NVLIST_ARRAY ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/ ** kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ **,int) ; 
 scalar_t__ nvlist_add_nvlist_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int) ; 
 scalar_t__ nvlist_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_remove (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_vdev_remove_aux(nvlist_t *config, char *name, nvlist_t **dev, int count,
    nvlist_t *dev_to_remove)
{
	nvlist_t **newdev = NULL;

	if (count > 1)
		newdev = kmem_alloc((count - 1) * sizeof (void *), KM_SLEEP);

	for (int i = 0, j = 0; i < count; i++) {
		if (dev[i] == dev_to_remove)
			continue;
		VERIFY(nvlist_dup(dev[i], &newdev[j++], KM_SLEEP) == 0);
	}

	VERIFY(nvlist_remove(config, name, DATA_TYPE_NVLIST_ARRAY) == 0);
	VERIFY(nvlist_add_nvlist_array(config, name, newdev, count - 1) == 0);

	for (int i = 0; i < count - 1; i++)
		nvlist_free(newdev[i]);

	if (count > 1)
		kmem_free(newdev, (count - 1) * sizeof (void *));
}