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

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERRNO_RESTORE () ; 
 int /*<<< orphan*/  ERRNO_SAVE () ; 
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_TYPE_NUMBER_ARRAY ; 
 int /*<<< orphan*/  nv_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvpair_allocv (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 

nvpair_t *
nvpair_move_number_array(const char *name, uint64_t *value, size_t nitems)
{
	nvpair_t *nvp;

	if (value == NULL || nitems == 0) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	nvp = nvpair_allocv(name, NV_TYPE_NUMBER_ARRAY,
	    (uint64_t)(uintptr_t)value, sizeof(value[0]) * nitems, nitems);
	if (nvp == NULL) {
		ERRNO_SAVE();
		nv_free(value);
		ERRNO_RESTORE();
	}

	return (nvp);
}