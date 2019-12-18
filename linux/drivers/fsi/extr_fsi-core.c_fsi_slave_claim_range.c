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
typedef  scalar_t__ uint32_t ;
struct fsi_slave {scalar_t__ size; } ;

/* Variables and functions */
 int EINVAL ; 

extern int fsi_slave_claim_range(struct fsi_slave *slave,
		uint32_t addr, uint32_t size)
{
	if (addr + size < addr)
		return -EINVAL;

	if (addr + size > slave->size)
		return -EINVAL;

	/* todo: check for overlapping claims */
	return 0;
}