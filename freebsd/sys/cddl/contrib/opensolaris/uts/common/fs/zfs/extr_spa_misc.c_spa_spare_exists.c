#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_aux_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_spare_avl ; 
 int /*<<< orphan*/  spa_spare_lock ; 

boolean_t
spa_spare_exists(uint64_t guid, uint64_t *pool, int *refcnt)
{
	boolean_t found;

	mutex_enter(&spa_spare_lock);
	found = spa_aux_exists(guid, pool, refcnt, &spa_spare_avl);
	mutex_exit(&spa_spare_lock);

	return (found);
}