#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct nvlist_header {int dummy; } ;
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_11__ {scalar_t__ nvl_error; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__ const*) ; 
 scalar_t__ NV_TYPE_NVLIST ; 
 scalar_t__ NV_TYPE_NVLIST_ARRAY ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/ * nvlist_first_nvpair (TYPE_1__ const*) ; 
 TYPE_1__* nvlist_get_pararr (TYPE_1__ const*,void**) ; 
 scalar_t__ nvlist_in_array (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (TYPE_1__ const*,int /*<<< orphan*/  const*) ; 
 TYPE_1__* nvpair_get_nvlist (int /*<<< orphan*/  const*) ; 
 TYPE_1__** nvpair_get_nvlist_array (int /*<<< orphan*/  const*,size_t*) ; 
 int nvpair_header_size () ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/  const*) ; 
 scalar_t__ nvpair_size (int /*<<< orphan*/  const*) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

size_t
nvlist_size(const nvlist_t *nvl)
{
	const nvlist_t *tmpnvl;
	const nvlist_t * const *nvlarray;
	const nvpair_t *nvp, *tmpnvp;
	void *cookie;
	size_t size, nitems;
	unsigned int ii;

	NVLIST_ASSERT(nvl);
	PJDLOG_ASSERT(nvl->nvl_error == 0);

	size = sizeof(struct nvlist_header);
	nvp = nvlist_first_nvpair(nvl);
	while (nvp != NULL) {
		size += nvpair_header_size();
		size += strlen(nvpair_name(nvp)) + 1;
		if (nvpair_type(nvp) == NV_TYPE_NVLIST) {
			size += sizeof(struct nvlist_header);
			size += nvpair_header_size() + 1;
			tmpnvl = nvpair_get_nvlist(nvp);
			PJDLOG_ASSERT(tmpnvl->nvl_error == 0);
			tmpnvp = nvlist_first_nvpair(tmpnvl);
			if (tmpnvp != NULL) {
				nvl = tmpnvl;
				nvp = tmpnvp;
				continue;
			}
		} else if (nvpair_type(nvp) == NV_TYPE_NVLIST_ARRAY) {
			nvlarray = nvpair_get_nvlist_array(nvp, &nitems);
			PJDLOG_ASSERT(nitems > 0);

			size += (nvpair_header_size() + 1) * nitems;
			size += sizeof(struct nvlist_header) * nitems;

			tmpnvl = NULL;
			tmpnvp = NULL;
			for (ii = 0; ii < nitems; ii++) {
				PJDLOG_ASSERT(nvlarray[ii]->nvl_error == 0);
				tmpnvp = nvlist_first_nvpair(nvlarray[ii]);
				if (tmpnvp != NULL) {
					tmpnvl = nvlarray[ii];
					break;
				}
			}
			if (tmpnvp != NULL) {
				nvp = tmpnvp;
				nvl = tmpnvl;
				continue;
			}

		} else {
			size += nvpair_size(nvp);
		}

		while ((nvp = nvlist_next_nvpair(nvl, nvp)) == NULL) {
			do {
				cookie = NULL;
				nvl = nvlist_get_pararr(nvl, &cookie);
				if (nvl == NULL)
					goto out;
				if (nvlist_in_array(nvl) && cookie == NULL) {
					nvp = nvlist_first_nvpair(nvl);
				} else {
					nvp = cookie;
				}
			} while (nvp == NULL);
			if (nvlist_in_array(nvl) && cookie == NULL)
				break;
		}
	}

out:
	return (size);
}