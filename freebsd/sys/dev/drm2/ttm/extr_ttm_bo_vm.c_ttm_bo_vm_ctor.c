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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  scalar_t__ u_short ;
struct ucred {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
ttm_bo_vm_ctor(void *handle, vm_ooffset_t size, vm_prot_t prot,
    vm_ooffset_t foff, struct ucred *cred, u_short *color)
{

	/*
	 * On Linux, a reference to the buffer object is acquired here.
	 * The reason is that this function is not called when the
	 * mmap() is initialized, but only when a process forks for
	 * instance. Therefore on Linux, the reference on the bo is
	 * acquired either in ttm_bo_mmap() or ttm_bo_vm_open(). It's
	 * then released in ttm_bo_vm_close().
	 *
	 * Here, this function is called during mmap() initialization.
	 * Thus, the reference acquired in ttm_bo_mmap_single() is
	 * sufficient.
	 */

	*color = 0;
	return (0);
}