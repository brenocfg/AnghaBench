#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int ddi_copyin (void*,char*,size_t,int) ; 
 char* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,size_t) ; 
 int nvlist_unpack (char*,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioctl_compat_get_nvlist(uint64_t nvl, size_t size, int iflag,
    nvlist_t **nvp)
{
	char *packed;
	int error;
	nvlist_t *list = NULL;

	/*
	 * Read in and unpack the user-supplied nvlist.
	 */
	if (size == 0)
		return (EINVAL);

#ifdef _KERNEL
	packed = kmem_alloc(size, KM_SLEEP);
	if ((error = ddi_copyin((void *)(uintptr_t)nvl, packed, size,
	    iflag)) != 0) {
		kmem_free(packed, size);
		return (error);
	}
#else
	packed = (void *)(uintptr_t)nvl;
#endif

	error = nvlist_unpack(packed, size, &list, 0);

#ifdef _KERNEL
	kmem_free(packed, size);
#endif

	if (error != 0)
		return (error);

	*nvp = list;
	return (0);
}