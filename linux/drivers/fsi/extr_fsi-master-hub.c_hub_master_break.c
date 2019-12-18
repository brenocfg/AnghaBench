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
struct fsi_master {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int hub_master_write (struct fsi_master*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hub_master_break(struct fsi_master *master, int link)
{
	uint32_t addr;
	__be32 cmd;

	addr = 0x4;
	cmd = cpu_to_be32(0xc0de0000);

	return hub_master_write(master, link, 0, addr, &cmd, sizeof(cmd));
}