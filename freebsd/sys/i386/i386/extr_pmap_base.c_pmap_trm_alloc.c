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
struct TYPE_2__ {void* (* pm_trm_alloc ) (size_t,int) ;} ;

/* Variables and functions */
 TYPE_1__* pmap_methods_ptr ; 
 void* stub1 (size_t,int) ; 

void *
pmap_trm_alloc(size_t size, int flags)
{

	return (pmap_methods_ptr->pm_trm_alloc(size, flags));
}