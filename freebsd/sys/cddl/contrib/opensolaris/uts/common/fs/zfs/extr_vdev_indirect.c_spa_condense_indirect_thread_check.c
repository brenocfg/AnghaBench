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
typedef  int /*<<< orphan*/  zthr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * spa_condensing_indirect; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */

__attribute__((used)) static boolean_t
spa_condense_indirect_thread_check(void *arg, zthr_t *zthr)
{
	spa_t *spa = arg;

	return (spa->spa_condensing_indirect != NULL);
}