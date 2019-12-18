#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {scalar_t__ nvp_type; scalar_t__ nvp_nitems; scalar_t__ nvp_data; } ;
typedef  TYPE_1__ nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  nvl ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVPAIR_ASSERT (TYPE_1__*) ; 
 int NV_FLAG_IN_ARRAY ; 
 int /*<<< orphan*/  NV_TYPE_NVLIST ; 
 scalar_t__ NV_TYPE_NVLIST_ARRAY ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/ * nvlist_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_error (int /*<<< orphan*/  const*) ; 
 int nvlist_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_get_pararr (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_set_array_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_set_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvlist_set_parent (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* nvpair_allocv (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvpair_append (TYPE_1__*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvpair_free (TYPE_1__*) ; 

int
nvpair_append_nvlist_array(nvpair_t *nvp, const nvlist_t *value)
{
	nvpair_t *tmpnvp;
	nvlist_t *nvl, *prev;
	int flags;

	NVPAIR_ASSERT(nvp);
	PJDLOG_ASSERT(nvp->nvp_type == NV_TYPE_NVLIST_ARRAY);
	if (value == NULL || nvlist_error(value) != 0 ||
	    nvlist_get_pararr(value, NULL) != NULL) {
		ERRNO_SET(EINVAL);
		return (-1);
	}
	nvl = nvlist_clone(value);
	if (nvl == NULL) {
		return (-1);
	}
	flags = nvlist_flags(nvl) | NV_FLAG_IN_ARRAY;
	nvlist_set_flags(nvl, flags);

	tmpnvp = NULL;
	prev = NULL;
	if (nvp->nvp_nitems > 0) {
		nvlist_t **nvls = (void *)(uintptr_t)nvp->nvp_data;

		prev = nvls[nvp->nvp_nitems - 1];
		PJDLOG_ASSERT(prev != NULL);

		tmpnvp = nvpair_allocv(" ", NV_TYPE_NVLIST,
		    (uint64_t)(uintptr_t)nvl, 0, 0);
		if (tmpnvp == NULL) {
			goto fail;
		}
	}
	if (nvpair_append(nvp, &nvl, sizeof(nvl), 0) == -1) {
		goto fail;
	}
	if (tmpnvp) {
		NVPAIR_ASSERT(tmpnvp);
		nvlist_set_array_next(prev, tmpnvp);
	}
	nvlist_set_parent(nvl, nvp);
	return (0);
fail:
	if (tmpnvp) {
		nvpair_free(tmpnvp);
	}
	nvlist_destroy(nvl);
	return (-1);
}