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

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  vm_get_highmem_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_get_lowmem_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cb_getmem(void *arg, uint64_t *ret_lowmem, uint64_t *ret_highmem)
{

	*ret_lowmem = vm_get_lowmem_size(ctx);
	*ret_highmem = vm_get_highmem_size(ctx);
}