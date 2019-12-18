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
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_4__ {int /*<<< orphan*/ * nvl_array_next; int /*<<< orphan*/  nvl_flags; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  NV_FLAG_IN_ARRAY ; 
 int /*<<< orphan*/  nv_free (int /*<<< orphan*/ *) ; 

void
nvlist_set_array_next(nvlist_t *nvl, nvpair_t *ele)
{

	NVLIST_ASSERT(nvl);

	if (ele != NULL) {
		nvl->nvl_flags |= NV_FLAG_IN_ARRAY;
	} else {
		nvl->nvl_flags &= ~NV_FLAG_IN_ARRAY;
		nv_free(nvl->nvl_array_next);
	}

	nvl->nvl_array_next = ele;
}