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
struct TYPE_3__ {int sav_count; int /*<<< orphan*/ * sav_vdevs; } ;
typedef  TYPE_1__ spa_aux_vdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  spa_check_removed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_aux_check_removed(spa_aux_vdev_t *sav)
{
	int i;

	for (i = 0; i < sav->sav_count; i++)
		spa_check_removed(sav->sav_vdevs[i]);
}