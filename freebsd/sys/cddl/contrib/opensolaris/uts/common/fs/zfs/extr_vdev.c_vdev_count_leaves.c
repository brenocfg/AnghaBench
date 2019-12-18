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
struct TYPE_3__ {int /*<<< orphan*/  spa_root_vdev; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int vdev_count_leaves_impl (int /*<<< orphan*/ ) ; 

int
vdev_count_leaves(spa_t *spa)
{
	return (vdev_count_leaves_impl(spa->spa_root_vdev));
}