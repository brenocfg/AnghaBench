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
typedef  scalar_t__ vm_paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  __syncicache (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
moea_syncicache(vm_paddr_t pa, vm_size_t len)
{
	__syncicache((void *)pa, len);
}