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
struct pmap_kernel_map_range {int /*<<< orphan*/  attrs; int /*<<< orphan*/  sva; } ;
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pmap_kernel_map_range*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sysctl_kmaps_reinit(struct pmap_kernel_map_range *range, vm_offset_t va,
    pt_entry_t attrs)
{

	memset(range, 0, sizeof(*range));
	range->sva = va;
	range->attrs = attrs;
}