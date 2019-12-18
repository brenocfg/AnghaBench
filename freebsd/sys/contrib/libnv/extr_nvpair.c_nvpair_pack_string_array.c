#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nvp_type; size_t nvp_datasize; unsigned int nvp_nitems; } ;
typedef  TYPE_1__ nvpair_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVPAIR_ASSERT (TYPE_1__ const*) ; 
 scalar_t__ NV_TYPE_STRING_ARRAY ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,size_t) ; 
 char** nvpair_get_string_array (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int strlen (char const* const) ; 

unsigned char *
nvpair_pack_string_array(const nvpair_t *nvp, unsigned char *ptr, size_t *leftp)
{
	unsigned int ii;
	size_t size, len;
	const char * const *array;

	NVPAIR_ASSERT(nvp);
	PJDLOG_ASSERT(nvp->nvp_type == NV_TYPE_STRING_ARRAY);
	PJDLOG_ASSERT(*leftp >= nvp->nvp_datasize);

	size = 0;
	array = nvpair_get_string_array(nvp, NULL);
	PJDLOG_ASSERT(array != NULL);

	for (ii = 0; ii < nvp->nvp_nitems; ii++) {
		len = strlen(array[ii]) + 1;
		PJDLOG_ASSERT(*leftp >= len);

		memcpy(ptr, (const void *)array[ii], len);
		size += len;
		ptr += len;
		*leftp -= len;
	}

	PJDLOG_ASSERT(size == nvp->nvp_datasize);

	return (ptr);
}