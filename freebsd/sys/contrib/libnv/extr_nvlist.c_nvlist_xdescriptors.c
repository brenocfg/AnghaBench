#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_9__ {scalar_t__ nvl_error; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__ const*) ; 
#define  NV_TYPE_DESCRIPTOR 131 
#define  NV_TYPE_DESCRIPTOR_ARRAY 130 
#define  NV_TYPE_NVLIST 129 
#define  NV_TYPE_NVLIST_ARRAY 128 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 TYPE_1__* nvlist_get_pararr (TYPE_1__ const*,void**) ; 
 int /*<<< orphan*/ * nvlist_next (TYPE_1__ const*,int*,void**) ; 
 int nvpair_get_descriptor (int /*<<< orphan*/ *) ; 
 int* nvpair_get_descriptor_array (int /*<<< orphan*/ *,size_t*) ; 
 TYPE_1__* nvpair_get_nvlist (int /*<<< orphan*/ *) ; 
 TYPE_1__** nvpair_get_nvlist_array (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int *
nvlist_xdescriptors(const nvlist_t *nvl, int *descs)
{
	void *cookie;
	nvpair_t *nvp;
	int type;

	NVLIST_ASSERT(nvl);
	PJDLOG_ASSERT(nvl->nvl_error == 0);

	cookie = NULL;
	do {
		while (nvlist_next(nvl, &type, &cookie) != NULL) {
			nvp = cookie;
			switch (type) {
			case NV_TYPE_DESCRIPTOR:
				*descs = nvpair_get_descriptor(nvp);
				descs++;
				break;
			case NV_TYPE_DESCRIPTOR_ARRAY:
			    {
				const int *value;
				size_t nitems;
				unsigned int ii;

				value = nvpair_get_descriptor_array(nvp,
				    &nitems);
				for (ii = 0; ii < nitems; ii++) {
					*descs = value[ii];
					descs++;
				}
				break;
			    }
			case NV_TYPE_NVLIST:
				nvl = nvpair_get_nvlist(nvp);
				cookie = NULL;
				break;
			case NV_TYPE_NVLIST_ARRAY:
			    {
				const nvlist_t * const *value;
				size_t nitems;

				value = nvpair_get_nvlist_array(nvp, &nitems);
				PJDLOG_ASSERT(value != NULL);
				PJDLOG_ASSERT(nitems > 0);

				nvl = value[0];
				cookie = NULL;
				break;
			    }
			}
		}
	} while ((nvl = nvlist_get_pararr(nvl, &cookie)) != NULL);

	return (descs);
}