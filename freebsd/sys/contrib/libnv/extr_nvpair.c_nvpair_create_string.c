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
 int /*<<< orphan*/  NV_TYPE_STRING ; 
 int /*<<< orphan*/  nv_free (char*) ; 
 char* nv_strdup (char const*) ; 
 int /*<<< orphan*/ * nvpair_allocv (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

nvpair_t *
nvpair_create_string(const char *name, const char *value)
{
	nvpair_t *nvp;
	size_t size;
	char *data;

	if (value == NULL) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	data = nv_strdup(value);
	if (data == NULL)
		return (NULL);
	size = strlen(value) + 1;

	nvp = nvpair_allocv(name, NV_TYPE_STRING, (uint64_t)(uintptr_t)data,
	    size, 0);
	if (nvp == NULL)
		nv_free(data);

	return (nvp);
}