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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  spa_guid; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int vdev_probe (int /*<<< orphan*/ ,void*,TYPE_1__**) ; 
 int /*<<< orphan*/  vdev_read ; 

__attribute__((used)) static int
zfs_probe(int fd, uint64_t *pool_guid)
{
	spa_t *spa;
	int ret;

	spa = NULL;
	ret = vdev_probe(vdev_read, (void *)(uintptr_t)fd, &spa);
	if (ret == 0 && pool_guid != NULL)
		*pool_guid = spa->spa_guid;
	return (ret);
}