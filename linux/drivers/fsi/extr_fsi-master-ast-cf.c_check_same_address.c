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
typedef  int uint32_t ;
struct fsi_master_acf {int last_addr; } ;

/* Variables and functions */

__attribute__((used)) static bool check_same_address(struct fsi_master_acf *master, int id,
			       uint32_t addr)
{
	/* this will also handle LAST_ADDR_INVALID */
	return master->last_addr == (((id & 0x3) << 21) | (addr & ~0x3));
}