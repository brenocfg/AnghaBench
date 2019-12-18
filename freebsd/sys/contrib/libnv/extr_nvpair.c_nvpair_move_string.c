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

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERRNO_RESTORE () ; 
 int /*<<< orphan*/  ERRNO_SAVE () ; 
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_TYPE_STRING ; 
 int /*<<< orphan*/  nv_free (char*) ; 
 int /*<<< orphan*/ * nvpair_allocv (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

nvpair_t *
nvpair_move_string(const char *name, char *value)
{
	nvpair_t *nvp;

	if (value == NULL) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	nvp = nvpair_allocv(name, NV_TYPE_STRING, (uint64_t)(uintptr_t)value,
	    strlen(value) + 1, 0);
	if (nvp == NULL) {
		ERRNO_SAVE();
		nv_free(value);
		ERRNO_RESTORE();
	}

	return (nvp);
}