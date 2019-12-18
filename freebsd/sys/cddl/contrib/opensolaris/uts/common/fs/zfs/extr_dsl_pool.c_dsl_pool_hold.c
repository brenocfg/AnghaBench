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
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_pool_config_enter (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * spa_get_dsl (int /*<<< orphan*/ *) ; 
 int spa_open (char const*,int /*<<< orphan*/ **,void*) ; 

int
dsl_pool_hold(const char *name, void *tag, dsl_pool_t **dp)
{
	spa_t *spa;
	int error;

	error = spa_open(name, &spa, tag);
	if (error == 0) {
		*dp = spa_get_dsl(spa);
		dsl_pool_config_enter(*dp, tag);
	}
	return (error);
}