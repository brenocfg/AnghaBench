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
struct TYPE_4__ {scalar_t__ nvp_type; size_t nvp_nitems; scalar_t__ nvp_data; } ;
typedef  TYPE_1__ nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVPAIR_ASSERT (TYPE_1__ const*) ; 
 scalar_t__ NV_TYPE_NVLIST_ARRAY ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 

const nvlist_t * const *
nvpair_get_nvlist_array(const nvpair_t *nvp, size_t *nitems)
{

	NVPAIR_ASSERT(nvp);
	PJDLOG_ASSERT(nvp->nvp_type == NV_TYPE_NVLIST_ARRAY);

	if (nitems != NULL)
		*nitems = nvp->nvp_nitems;

	return ((const nvlist_t * const *)((intptr_t)nvp->nvp_data));
}