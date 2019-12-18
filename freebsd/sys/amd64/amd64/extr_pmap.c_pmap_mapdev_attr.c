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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;

/* Variables and functions */
 int MAPDEV_FLUSHCACHE ; 
 int MAPDEV_SETATTR ; 
 void* pmap_mapdev_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void *
pmap_mapdev_attr(vm_paddr_t pa, vm_size_t size, int mode)
{

	return (pmap_mapdev_internal(pa, size, mode, MAPDEV_FLUSHCACHE |
	    MAPDEV_SETATTR));
}