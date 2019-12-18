#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * vdev_ops; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  metaslab_check_free_impl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_indirect_ops ; 

__attribute__((used)) static void
metaslab_check_free_impl_cb(uint64_t inner, vdev_t *vd, uint64_t offset,
    uint64_t size, void *arg)
{
	if (vd->vdev_ops == &vdev_indirect_ops)
		return;

	metaslab_check_free_impl(vd, offset, size);
}