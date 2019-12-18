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
struct sec_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sec_clk_dis (struct sec_dev_info*) ; 
 int /*<<< orphan*/  sec_hw_exit (struct sec_dev_info*) ; 

__attribute__((used)) static void sec_base_exit(struct sec_dev_info *info)
{
	sec_hw_exit(info);
	sec_clk_dis(info);
}