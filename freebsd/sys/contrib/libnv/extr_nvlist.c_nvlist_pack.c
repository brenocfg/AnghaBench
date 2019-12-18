#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nvl_error; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 scalar_t__ EOPNOTSUPP ; 
 int /*<<< orphan*/  ERRNO_SET (scalar_t__) ; 
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__ const*) ; 
 scalar_t__ nvlist_ndescriptors (TYPE_1__ const*) ; 
 void* nvlist_xpack (TYPE_1__ const*,int /*<<< orphan*/ *,size_t*) ; 

void *
nvlist_pack(const nvlist_t *nvl, size_t *sizep)
{

	NVLIST_ASSERT(nvl);

	if (nvl->nvl_error != 0) {
		ERRNO_SET(nvl->nvl_error);
		return (NULL);
	}

	if (nvlist_ndescriptors(nvl) > 0) {
		ERRNO_SET(EOPNOTSUPP);
		return (NULL);
	}

	return (nvlist_xpack(nvl, NULL, sizep));
}