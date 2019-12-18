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
struct netmap_mem_d {TYPE_1__* ops; } ;
struct netmap_lut {int dummy; } ;
struct TYPE_2__ {int (* nmd_get_lut ) (struct netmap_mem_d*,struct netmap_lut*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NMA_LOCK (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  NMA_UNLOCK (struct netmap_mem_d*) ; 
 int stub1 (struct netmap_mem_d*,struct netmap_lut*) ; 

int
netmap_mem_get_lut(struct netmap_mem_d *nmd, struct netmap_lut *lut)
{
	int rv;

	NMA_LOCK(nmd);
	rv = nmd->ops->nmd_get_lut(nmd, lut);
	NMA_UNLOCK(nmd);

	return rv;
}