#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  spa_inject_ref; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_1__* spa_lookup (char*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 

spa_t *
spa_inject_addref(char *name)
{
	spa_t *spa;

	mutex_enter(&spa_namespace_lock);
	if ((spa = spa_lookup(name)) == NULL) {
		mutex_exit(&spa_namespace_lock);
		return (NULL);
	}
	spa->spa_inject_ref++;
	mutex_exit(&spa_namespace_lock);

	return (spa);
}