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
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* arch_zfs_probe ) () ;} ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/ * STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * STAILQ_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_AFTER (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ archsw ; 
 int /*<<< orphan*/  spa_link ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  zfs_init () ; 
 int /*<<< orphan*/  zfs_pools ; 
 scalar_t__ zfs_spa_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_dev_init(void)
{
	spa_t *spa;
	spa_t *next;
	spa_t *prev;

	zfs_init();
	if (archsw.arch_zfs_probe == NULL)
		return (ENXIO);
	archsw.arch_zfs_probe();

	prev = NULL;
	spa = STAILQ_FIRST(&zfs_pools);
	while (spa != NULL) {
		next = STAILQ_NEXT(spa, spa_link);
		if (zfs_spa_init(spa)) {
			if (prev == NULL)
				STAILQ_REMOVE_HEAD(&zfs_pools, spa_link);
			else
				STAILQ_REMOVE_AFTER(&zfs_pools, prev, spa_link);
		} else
			prev = spa;
		spa = next;
	}
	return (0);
}