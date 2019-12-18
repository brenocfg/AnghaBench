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
struct netmap_mem_d {int flags; int lasterr; } ;

/* Variables and functions */
 int NETMAP_MEM_FINALIZED ; 
 scalar_t__ netmap_mem_finalize_all (struct netmap_mem_d*) ; 

__attribute__((used)) static int
netmap_mem2_finalize(struct netmap_mem_d *nmd)
{
	if (nmd->flags & NETMAP_MEM_FINALIZED)
		goto out;

	if (netmap_mem_finalize_all(nmd))
		goto out;

	nmd->lasterr = 0;

out:
	return nmd->lasterr;
}