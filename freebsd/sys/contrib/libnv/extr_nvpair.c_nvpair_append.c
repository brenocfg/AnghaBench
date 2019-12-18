#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {size_t nvp_nitems; size_t nvp_datasize; scalar_t__ nvp_data; } ;
typedef  TYPE_1__ nvpair_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 void* nv_realloc (void*,size_t) ; 

__attribute__((used)) static int
nvpair_append(nvpair_t *nvp, const void *value, size_t valsize, size_t datasize)
{
	void *olddata, *data, *valp;
	size_t oldlen;

	oldlen = nvp->nvp_nitems * valsize;
	olddata = (void *)(uintptr_t)nvp->nvp_data;
	data = nv_realloc(olddata, oldlen + valsize);
	if (data == NULL) {
		ERRNO_SET(ENOMEM);
		return (-1);
	}
	valp = (unsigned char *)data + oldlen;
	memcpy(valp, value, valsize);

	nvp->nvp_data = (uint64_t)(uintptr_t)data;
	nvp->nvp_datasize += datasize;
	nvp->nvp_nitems++;
	return (0);
}