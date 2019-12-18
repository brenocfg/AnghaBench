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
struct TYPE_4__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_pool_config_exit (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ ,void*) ; 

void
dsl_pool_rele(dsl_pool_t *dp, void *tag)
{
	dsl_pool_config_exit(dp, tag);
	spa_close(dp->dp_spa, tag);
}