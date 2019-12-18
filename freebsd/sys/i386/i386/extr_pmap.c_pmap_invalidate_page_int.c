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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  invlpg (int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_pmap ; 

__attribute__((used)) static void
pmap_invalidate_page_int(pmap_t pmap, vm_offset_t va)
{

	if (pmap == kernel_pmap)
		invlpg(va);
}