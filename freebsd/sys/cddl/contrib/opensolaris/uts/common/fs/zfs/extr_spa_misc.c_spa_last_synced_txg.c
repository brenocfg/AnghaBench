#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  ub_txg; } ;
struct TYPE_5__ {TYPE_1__ spa_ubsync; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */

uint64_t
spa_last_synced_txg(spa_t *spa)
{
	return (spa->spa_ubsync.ub_txg);
}