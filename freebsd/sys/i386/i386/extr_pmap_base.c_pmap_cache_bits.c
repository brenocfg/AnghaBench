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
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int (* pm_cache_bits ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* pmap_methods_ptr ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
pmap_cache_bits(pmap_t pmap, int mode, boolean_t is_pde)
{

	return (pmap_methods_ptr->pm_cache_bits(pmap, mode, is_pde));
}