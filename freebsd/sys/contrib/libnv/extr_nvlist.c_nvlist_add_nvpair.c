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
struct TYPE_6__ {int nvl_flags; int /*<<< orphan*/  nvl_head; int /*<<< orphan*/  nvl_error; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERRNO_OR_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRNO_SET (scalar_t__) ; 
 int /*<<< orphan*/  NVPAIR_ASSERT (int /*<<< orphan*/  const*) ; 
 int NV_FLAG_NO_UNIQUE ; 
 scalar_t__ nvlist_error (TYPE_1__*) ; 
 scalar_t__ nvlist_exists (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvpair_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nvpair_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/  const*) ; 

void
nvlist_add_nvpair(nvlist_t *nvl, const nvpair_t *nvp)
{
	nvpair_t *newnvp;

	NVPAIR_ASSERT(nvp);

	if (nvlist_error(nvl) != 0) {
		ERRNO_SET(nvlist_error(nvl));
		return;
	}
	if ((nvl->nvl_flags & NV_FLAG_NO_UNIQUE) == 0) {
		if (nvlist_exists(nvl, nvpair_name(nvp))) {
			nvl->nvl_error = EEXIST;
			ERRNO_SET(nvlist_error(nvl));
			return;
		}
	}

	newnvp = nvpair_clone(nvp);
	if (newnvp == NULL) {
		nvl->nvl_error = ERRNO_OR_DEFAULT(ENOMEM);
		ERRNO_SET(nvlist_error(nvl));
		return;
	}

	nvpair_insert(&nvl->nvl_head, newnvp, nvl);
}