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
typedef  scalar_t__ vm_ooffset_t ;
typedef  scalar_t__ u_short ;
struct ucred {int dummy; } ;
struct netmap_vm_handle_t {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_ref (int /*<<< orphan*/ ) ; 
 scalar_t__ netmap_verbose ; 
 int /*<<< orphan*/  nm_prinf (char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netmap_dev_pager_ctor(void *handle, vm_ooffset_t size, vm_prot_t prot,
		vm_ooffset_t foff, struct ucred *cred, u_short *color)
{
	struct netmap_vm_handle_t *vmh = handle;

	if (netmap_verbose)
		nm_prinf("handle %p size %jd prot %d foff %jd",
			handle, (intmax_t)size, prot, (intmax_t)foff);
	if (color)
		*color = 0;
	dev_ref(vmh->dev);
	return 0;
}