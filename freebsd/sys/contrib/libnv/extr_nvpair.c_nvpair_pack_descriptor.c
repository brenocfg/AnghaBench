#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
struct TYPE_4__ {scalar_t__ nvp_type; scalar_t__ nvp_data; } ;
typedef  TYPE_1__ nvpair_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVPAIR_ASSERT (TYPE_1__ const*) ; 
 scalar_t__ NV_TYPE_DESCRIPTOR ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int*,int) ; 

unsigned char *
nvpair_pack_descriptor(const nvpair_t *nvp, unsigned char *ptr, int64_t *fdidxp,
    size_t *leftp)
{
	int64_t value;

	NVPAIR_ASSERT(nvp);
	PJDLOG_ASSERT(nvp->nvp_type == NV_TYPE_DESCRIPTOR);

	value = (int64_t)nvp->nvp_data;
	if (value != -1) {
		/*
		 * If there is a real descriptor here, we change its number
		 * to position in the array of descriptors send via control
		 * message.
		 */
		PJDLOG_ASSERT(fdidxp != NULL);

		value = *fdidxp;
		(*fdidxp)++;
	}

	PJDLOG_ASSERT(*leftp >= sizeof(value));
	memcpy(ptr, &value, sizeof(value));
	ptr += sizeof(value);
	*leftp -= sizeof(value);

	return (ptr);
}