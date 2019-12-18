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
struct TYPE_4__ {scalar_t__ nvp_type; size_t nvp_datasize; scalar_t__ nvp_data; } ;
typedef  TYPE_1__ nvpair_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVPAIR_ASSERT (TYPE_1__ const*) ; 
 scalar_t__ NV_TYPE_BINARY ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,size_t) ; 

unsigned char *
nvpair_pack_binary(const nvpair_t *nvp, unsigned char *ptr, size_t *leftp)
{

	NVPAIR_ASSERT(nvp);
	PJDLOG_ASSERT(nvp->nvp_type == NV_TYPE_BINARY);

	PJDLOG_ASSERT(*leftp >= nvp->nvp_datasize);
	memcpy(ptr, (const void *)(intptr_t)nvp->nvp_data, nvp->nvp_datasize);
	ptr += nvp->nvp_datasize;
	*leftp -= nvp->nvp_datasize;

	return (ptr);
}