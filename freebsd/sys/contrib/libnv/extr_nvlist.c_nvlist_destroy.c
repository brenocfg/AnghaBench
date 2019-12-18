#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_7__ {scalar_t__ nvl_magic; int /*<<< orphan*/ * nvl_parent; int /*<<< orphan*/ * nvl_array_next; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERRNO_RESTORE () ; 
 int /*<<< orphan*/  ERRNO_SAVE () ; 
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  nv_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * nvlist_first_nvpair (TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_remove_nvpair (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_free_structure (int /*<<< orphan*/ *) ; 

void
nvlist_destroy(nvlist_t *nvl)
{
	nvpair_t *nvp;

	if (nvl == NULL)
		return;

	ERRNO_SAVE();

	NVLIST_ASSERT(nvl);

	while ((nvp = nvlist_first_nvpair(nvl)) != NULL) {
		nvlist_remove_nvpair(nvl, nvp);
		nvpair_free(nvp);
	}
	if (nvl->nvl_array_next != NULL)
		nvpair_free_structure(nvl->nvl_array_next);
	nvl->nvl_array_next = NULL;
	nvl->nvl_parent = NULL;
	nvl->nvl_magic = 0;
	nv_free(nvl);

	ERRNO_RESTORE();
}