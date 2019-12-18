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
struct arch_hw_breakpoint {int len; int type; int address; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBC_CAR (int) ; 
 int /*<<< orphan*/  UBC_CBR (int) ; 
 int UBC_CBR_CE ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh4a_ubc_enable(struct arch_hw_breakpoint *info, int idx)
{
	__raw_writel(UBC_CBR_CE | info->len | info->type, UBC_CBR(idx));
	__raw_writel(info->address, UBC_CAR(idx));
}