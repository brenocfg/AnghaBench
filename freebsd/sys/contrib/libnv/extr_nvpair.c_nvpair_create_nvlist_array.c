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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERRNO_RESTORE () ; 
 int /*<<< orphan*/  ERRNO_SAVE () ; 
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 int NV_FLAG_IN_ARRAY ; 
 int /*<<< orphan*/  NV_TYPE_NVLIST ; 
 int /*<<< orphan*/  NV_TYPE_NVLIST_ARRAY ; 
 int /*<<< orphan*/  nv_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** nv_malloc (int) ; 
 int /*<<< orphan*/ * nvlist_clone (int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int nvlist_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_set_array_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_set_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvlist_set_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvpair_allocv (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

nvpair_t *
nvpair_create_nvlist_array(const char *name, const nvlist_t * const *value,
    size_t nitems)
{
	unsigned int ii;
	nvlist_t **nvls;
	nvpair_t *parent;
	int flags;

	nvls = NULL;

	if (value == NULL || nitems == 0) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	nvls = nv_malloc(sizeof(value[0]) * nitems);
	if (nvls == NULL)
		return (NULL);

	for (ii = 0; ii < nitems; ii++) {
		if (value[ii] == NULL) {
			ERRNO_SET(EINVAL);
			goto fail;
		}

		nvls[ii] = nvlist_clone(value[ii]);
		if (nvls[ii] == NULL)
			goto fail;

		if (ii > 0) {
			nvpair_t *nvp;

			nvp = nvpair_allocv(" ", NV_TYPE_NVLIST,
			    (uint64_t)(uintptr_t)nvls[ii], 0, 0);
			if (nvp == NULL) {
				ERRNO_SAVE();
				nvlist_destroy(nvls[ii]);
				ERRNO_RESTORE();
				goto fail;
			}
			nvlist_set_array_next(nvls[ii - 1], nvp);
		}
	}
	flags = nvlist_flags(nvls[nitems - 1]) | NV_FLAG_IN_ARRAY;
	nvlist_set_flags(nvls[nitems - 1], flags);

	parent = nvpair_allocv(name, NV_TYPE_NVLIST_ARRAY,
	    (uint64_t)(uintptr_t)nvls, 0, nitems);
	if (parent == NULL)
		goto fail;

	for (ii = 0; ii < nitems; ii++)
		nvlist_set_parent(nvls[ii], parent);

	return (parent);

fail:
	ERRNO_SAVE();
	for (; ii > 0; ii--)
		nvlist_destroy(nvls[ii - 1]);
	nv_free(nvls);
	ERRNO_RESTORE();

	return (NULL);
}