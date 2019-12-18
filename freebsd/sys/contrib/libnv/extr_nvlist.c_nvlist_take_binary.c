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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_TYPE_BINARY ; 
 int /*<<< orphan*/ * nvlist_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  nvlist_remove_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_report_missing (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  nvpair_free_structure (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_get_binary (int /*<<< orphan*/ *,size_t*) ; 

void *
nvlist_take_binary(nvlist_t *nvl, const char *name, size_t *sizep)
{
	nvpair_t *nvp;
	void *value;

	nvp = nvlist_find(nvl, NV_TYPE_BINARY, name);
	if (nvp == NULL)
		nvlist_report_missing(NV_TYPE_BINARY, name);

	value = (void *)(intptr_t)nvpair_get_binary(nvp, sizep);
	nvlist_remove_nvpair(nvl, nvp);
	nvpair_free_structure(nvp);
	return (value);
}