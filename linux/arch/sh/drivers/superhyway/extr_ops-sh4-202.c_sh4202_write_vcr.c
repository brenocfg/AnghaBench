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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct superhyway_vcr_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (int,unsigned long) ; 

__attribute__((used)) static int sh4202_write_vcr(unsigned long base, struct superhyway_vcr_info vcr)
{
	u64 tmp = *(u64 *)&vcr;

	__raw_writel((tmp >> 32) & 0xffffffff, base);
	__raw_writel(tmp & 0xffffffff, base + sizeof(u32));

	return 0;
}