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
struct TYPE_6__ {scalar_t__ nvl_error; int nvl_flags; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__ const*) ; 
 int NV_FLAG_IGNORE_CASE ; 
 int NV_TYPE_FIRST ; 
 int NV_TYPE_LAST ; 
 int NV_TYPE_NONE ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/ * nvlist_first_nvpair (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static nvpair_t *
nvlist_find(const nvlist_t *nvl, int type, const char *name)
{
	nvpair_t *nvp;

	NVLIST_ASSERT(nvl);
	PJDLOG_ASSERT(nvl->nvl_error == 0);
	PJDLOG_ASSERT(type == NV_TYPE_NONE ||
	    (type >= NV_TYPE_FIRST && type <= NV_TYPE_LAST));

	for (nvp = nvlist_first_nvpair(nvl); nvp != NULL;
	    nvp = nvlist_next_nvpair(nvl, nvp)) {
		if (type != NV_TYPE_NONE && nvpair_type(nvp) != type)
			continue;
		if ((nvl->nvl_flags & NV_FLAG_IGNORE_CASE) != 0) {
			if (strcasecmp(nvpair_name(nvp), name) != 0)
				continue;
		} else {
			if (strcmp(nvpair_name(nvp), name) != 0)
				continue;
		}
		break;
	}

	if (nvp == NULL)
		ERRNO_SET(ENOENT);

	return (nvp);
}