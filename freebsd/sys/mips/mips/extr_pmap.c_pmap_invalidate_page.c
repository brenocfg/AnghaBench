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
struct pmap_invalidate_page_arg {int /*<<< orphan*/  va; int /*<<< orphan*/  pmap; } ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  pmap_call_on_active_cpus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pmap_invalidate_page_arg*) ; 
 int /*<<< orphan*/  pmap_invalidate_page_action ; 

__attribute__((used)) static void
pmap_invalidate_page(pmap_t pmap, vm_offset_t va)
{
	struct pmap_invalidate_page_arg arg;

	arg.pmap = pmap;
	arg.va = va;
	pmap_call_on_active_cpus(pmap, pmap_invalidate_page_action, &arg);
}