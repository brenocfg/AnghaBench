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
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  nv_free (void*) ; 
 void* nv_malloc (size_t) ; 
 int /*<<< orphan*/ * nvpair_allocv (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t) ; 

nvpair_t *
nvpair_create_number_array(const char *name, const uint64_t *value,
    size_t nitems)
{
	nvpair_t *nvp;
	size_t size;
	void *data;

	if (value == NULL || nitems == 0) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	size = sizeof(value[0]) * nitems;
	data = nv_malloc(size);
	if (data == NULL)
		return (NULL);

	memcpy(data, value, size);
	nvp = nvpair_allocv(name, NV_TYPE_NUMBER_ARRAY,
	    (uint64_t)(uintptr_t)data, size, nitems);
	if (nvp == NULL) {
		ERRNO_SAVE();
		nv_free(data);
		ERRNO_RESTORE();
	}

	return (nvp);
}