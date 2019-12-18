#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_10__ {scalar_t__ nvl_error; int nvl_flags; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERRNO_SET (scalar_t__) ; 
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__ const*) ; 
 int NV_FLAG_PUBLIC_MASK ; 
 TYPE_1__* nvlist_create (int) ; 
 int /*<<< orphan*/  nvlist_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/ * nvlist_first_nvpair (TYPE_1__ const*) ; 
 int /*<<< orphan*/  nvlist_move_nvpair (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvpair_clone (int /*<<< orphan*/ *) ; 

nvlist_t *
nvlist_clone(const nvlist_t *nvl)
{
	nvlist_t *newnvl;
	nvpair_t *nvp, *newnvp;

	NVLIST_ASSERT(nvl);

	if (nvl->nvl_error != 0) {
		ERRNO_SET(nvl->nvl_error);
		return (NULL);
	}

	newnvl = nvlist_create(nvl->nvl_flags & NV_FLAG_PUBLIC_MASK);
	for (nvp = nvlist_first_nvpair(nvl); nvp != NULL;
	    nvp = nvlist_next_nvpair(nvl, nvp)) {
		newnvp = nvpair_clone(nvp);
		if (newnvp == NULL)
			break;
		(void)nvlist_move_nvpair(newnvl, newnvp);
	}
	if (nvp != NULL) {
		nvlist_destroy(newnvl);
		return (NULL);
	}
	return (newnvl);
}