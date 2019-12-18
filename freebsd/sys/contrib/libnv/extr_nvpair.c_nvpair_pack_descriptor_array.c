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
typedef  int /*<<< orphan*/  value ;
struct TYPE_5__ {scalar_t__ nvp_type; size_t nvp_datasize; unsigned int nvp_nitems; } ;
typedef  TYPE_1__ nvpair_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVPAIR_ASSERT (TYPE_1__ const*) ; 
 scalar_t__ NV_TYPE_DESCRIPTOR_ARRAY ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int*,int) ; 
 int* nvpair_get_descriptor_array (TYPE_1__ const*,int /*<<< orphan*/ *) ; 

unsigned char *
nvpair_pack_descriptor_array(const nvpair_t *nvp, unsigned char *ptr,
    int64_t *fdidxp, size_t *leftp)
{
	int64_t value;
	const int *array;
	unsigned int ii;

	NVPAIR_ASSERT(nvp);
	PJDLOG_ASSERT(nvp->nvp_type == NV_TYPE_DESCRIPTOR_ARRAY);
	PJDLOG_ASSERT(*leftp >= nvp->nvp_datasize);

	array = nvpair_get_descriptor_array(nvp, NULL);
	PJDLOG_ASSERT(array != NULL);

	for (ii = 0; ii < nvp->nvp_nitems; ii++) {
		PJDLOG_ASSERT(*leftp >= sizeof(value));

		value = array[ii];
		if (value != -1) {
			/*
			 * If there is a real descriptor here, we change its
			 * number to position in the array of descriptors send
			 * via control message.
			 */
			PJDLOG_ASSERT(fdidxp != NULL);

			value = *fdidxp;
			(*fdidxp)++;
		}
		memcpy(ptr, &value, sizeof(value));
		ptr += sizeof(value);
		*leftp -= sizeof(value);
	}

	return (ptr);
}