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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ spa_final_txg; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 scalar_t__ TXG_DEFER_SIZE ; 

uint64_t
spa_final_dirty_txg(spa_t *spa)
{
	return (spa->spa_final_txg - TXG_DEFER_SIZE);
}