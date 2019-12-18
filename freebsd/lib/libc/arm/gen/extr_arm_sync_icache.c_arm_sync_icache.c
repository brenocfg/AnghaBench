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
typedef  int /*<<< orphan*/  u_int ;
struct arm_sync_icache_args {int len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SYNC_ICACHE ; 
 int /*<<< orphan*/  sysarch (int /*<<< orphan*/ ,struct arm_sync_icache_args*) ; 

int
arm_sync_icache(u_int addr, int len)
{
	struct arm_sync_icache_args args;
	
	args.addr = addr;
	args.len  = len;
	sysarch(ARM_SYNC_ICACHE, &args);
	return (0);
}