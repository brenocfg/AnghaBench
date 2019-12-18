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
struct TYPE_3__ {int /*<<< orphan*/  spa_missing_tvds; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */

void
spa_set_missing_tvds(spa_t *spa, uint64_t missing)
{
	spa->spa_missing_tvds = missing;
}