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
struct pmap_kernel_map_range {int attrs; } ;
typedef  int pt_entry_t ;

/* Variables and functions */
 int PG_G ; 
 int PG_PDE_CACHE ; 
 int PG_PDE_PAT ; 
 int PG_RW ; 
 int PG_U ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int pg_nx ; 
 scalar_t__ pmap_pat_index (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
sysctl_kmaps_match(struct pmap_kernel_map_range *range, pt_entry_t attrs)
{
	pt_entry_t diff, mask;

	mask = pg_nx | PG_G | PG_RW | PG_U | PG_PDE_CACHE;
	diff = (range->attrs ^ attrs) & mask;
	if (diff == 0)
		return (true);
	if ((diff & ~PG_PDE_PAT) == 0 &&
	    pmap_pat_index(kernel_pmap, range->attrs, true) ==
	    pmap_pat_index(kernel_pmap, attrs, true))
		return (true);
	return (false);
}