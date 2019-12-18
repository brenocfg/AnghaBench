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
struct TYPE_3__ {size_t zc_nvlist_dst_size; scalar_t__ zc_nvlist_dst; int /*<<< orphan*/  zc_iflags; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_ENCODE_NATIVE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ ddi_copyout (char*,void*,size_t,int /*<<< orphan*/ ) ; 
 char* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,size_t) ; 
 scalar_t__ nvlist_pack (int /*<<< orphan*/ *,char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_size (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioctl_compat_put_nvlist(zfs_cmd_t *zc, nvlist_t *nvl)
{
	char *packed = NULL;
	int error = 0;
	size_t size;

	VERIFY(nvlist_size(nvl, &size, NV_ENCODE_NATIVE) == 0);

#ifdef _KERNEL
	packed = kmem_alloc(size, KM_SLEEP);
	VERIFY(nvlist_pack(nvl, &packed, &size, NV_ENCODE_NATIVE,
	    KM_SLEEP) == 0);

	if (ddi_copyout(packed,
	    (void *)(uintptr_t)zc->zc_nvlist_dst, size, zc->zc_iflags) != 0)
		error = EFAULT;
	kmem_free(packed, size);
#else
	packed = (void *)(uintptr_t)zc->zc_nvlist_dst;
	VERIFY(nvlist_pack(nvl, &packed, &size, NV_ENCODE_NATIVE,
	    0) == 0);
#endif

	zc->zc_nvlist_dst_size = size;
	return (error);
}