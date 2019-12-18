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
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_6__ {int /*<<< orphan*/ * nvl_parent; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__ const*) ; 
 TYPE_1__ const* nvpair_nvlist (int /*<<< orphan*/ *) ; 

const nvlist_t *
nvlist_get_parent(const nvlist_t *nvl, void **cookiep)
{
	nvpair_t *nvp;

	NVLIST_ASSERT(nvl);

	nvp = nvl->nvl_parent;
	if (cookiep != NULL)
		*cookiep = nvp;
	if (nvp == NULL)
		return (NULL);

	return (nvpair_nvlist(nvp));
}