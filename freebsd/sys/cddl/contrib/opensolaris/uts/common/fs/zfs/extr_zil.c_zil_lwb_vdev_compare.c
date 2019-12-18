#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  zv_vdev; } ;
typedef  TYPE_1__ zil_vdev_node_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int AVL_CMP (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
zil_lwb_vdev_compare(const void *x1, const void *x2)
{
	const uint64_t v1 = ((zil_vdev_node_t *)x1)->zv_vdev;
	const uint64_t v2 = ((zil_vdev_node_t *)x2)->zv_vdev;

	return (AVL_CMP(v1, v2));
}