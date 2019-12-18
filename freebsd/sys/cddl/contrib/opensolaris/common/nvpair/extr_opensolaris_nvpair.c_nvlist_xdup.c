#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  nvl_nvflag; } ;
typedef  TYPE_1__ nvlist_t ;
typedef  int /*<<< orphan*/  nv_alloc_t ;

/* Variables and functions */
 int EINVAL ; 
 int nvlist_copy_pairs (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_free (TYPE_1__*) ; 
 int nvlist_xalloc (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nvlist_xdup(nvlist_t *nvl, nvlist_t **nvlp, nv_alloc_t *nva)
{
	int err;
	nvlist_t *ret;

	if (nvl == NULL || nvlp == NULL)
		return (EINVAL);

	if ((err = nvlist_xalloc(&ret, nvl->nvl_nvflag, nva)) != 0)
		return (err);

	if ((err = nvlist_copy_pairs(nvl, ret)) != 0)
		nvlist_free(ret);
	else
		*nvlp = ret;

	return (err);
}