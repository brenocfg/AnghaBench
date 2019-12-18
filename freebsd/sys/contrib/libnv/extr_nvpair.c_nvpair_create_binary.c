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
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_TYPE_BINARY ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  nv_free (void*) ; 
 void* nv_malloc (size_t) ; 
 int /*<<< orphan*/ * nvpair_allocv (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

nvpair_t *
nvpair_create_binary(const char *name, const void *value, size_t size)
{
	nvpair_t *nvp;
	void *data;

	if (value == NULL || size == 0) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	data = nv_malloc(size);
	if (data == NULL)
		return (NULL);
	memcpy(data, value, size);

	nvp = nvpair_allocv(name, NV_TYPE_BINARY, (uint64_t)(uintptr_t)data,
	    size, 0);
	if (nvp == NULL)
		nv_free(data);

	return (nvp);
}