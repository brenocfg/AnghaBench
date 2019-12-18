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
struct netmap_mem_d {TYPE_1__* ops; scalar_t__ active; } ;
struct TYPE_2__ {int (* nmd_config ) (struct netmap_mem_d*) ;} ;

/* Variables and functions */
 int stub1 (struct netmap_mem_d*) ; 

__attribute__((used)) static int
netmap_mem_config(struct netmap_mem_d *nmd)
{
	if (nmd->active) {
		/* already in use. Not fatal, but we
		 * cannot change the configuration
		 */
		return 0;
	}

	return nmd->ops->nmd_config(nmd);
}