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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct nvd_disk {int /*<<< orphan*/  ns; } ;
struct disk {struct nvd_disk* d_drv1; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int nvme_ns_dump (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
nvd_dump(void *arg, void *virt, vm_offset_t phys, off_t offset, size_t len)
{
	struct disk *dp = arg;
	struct nvd_disk *ndisk = dp->d_drv1;

	return (nvme_ns_dump(ndisk->ns, virt, offset, len));
}