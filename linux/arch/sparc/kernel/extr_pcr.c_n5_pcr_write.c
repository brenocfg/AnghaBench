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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  sun4v_t5_set_perfreg (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void n5_pcr_write(unsigned long reg_num, u64 val)
{
	(void) sun4v_t5_set_perfreg(reg_num, val);
}