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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ ** kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
resize_configs(nvlist_t ***configs, uint64_t *count, uint64_t id)
{
	nvlist_t **new_configs;
	uint64_t i;

	if (id < *count)
		return;
	new_configs = kmem_zalloc((id + 1) * sizeof(nvlist_t *),
	    KM_SLEEP);
	for (i = 0; i < *count; i++)
		new_configs[i] = (*configs)[i];
	if (*configs != NULL)
		kmem_free(*configs, *count * sizeof(void *));
	*configs = new_configs;
	*count = id + 1;
}