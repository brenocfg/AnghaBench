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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_TYPE_NVLIST ; 
 int /*<<< orphan*/ * nvlist_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_set_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvpair_allocv (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

nvpair_t *
nvpair_create_nvlist(const char *name, const nvlist_t *value)
{
	nvlist_t *nvl;
	nvpair_t *nvp;

	if (value == NULL) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	nvl = nvlist_clone(value);
	if (nvl == NULL)
		return (NULL);

	nvp = nvpair_allocv(name, NV_TYPE_NVLIST, (uint64_t)(uintptr_t)nvl, 0,
	    0);
	if (nvp == NULL)
		nvlist_destroy(nvl);
	else
		nvlist_set_parent(nvl, nvp);

	return (nvp);
}