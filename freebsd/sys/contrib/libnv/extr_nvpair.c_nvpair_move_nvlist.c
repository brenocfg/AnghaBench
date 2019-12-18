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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  ERRNO_SET (scalar_t__) ; 
 int /*<<< orphan*/  NV_TYPE_NVLIST ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_get_nvpair_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_set_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvpair_allocv (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

nvpair_t *
nvpair_move_nvlist(const char *name, nvlist_t *value)
{
	nvpair_t *nvp;

	if (value == NULL || nvlist_get_nvpair_parent(value) != NULL) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	if (nvlist_error(value) != 0) {
		ERRNO_SET(nvlist_error(value));
		nvlist_destroy(value);
		return (NULL);
	}

	nvp = nvpair_allocv(name, NV_TYPE_NVLIST, (uint64_t)(uintptr_t)value,
	    0, 0);
	if (nvp == NULL)
		nvlist_destroy(value);
	else
		nvlist_set_parent(value, nvp);

	return (nvp);
}