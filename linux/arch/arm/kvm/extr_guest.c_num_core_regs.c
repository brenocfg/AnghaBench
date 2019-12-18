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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_regs {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long num_core_regs(void)
{
	return sizeof(struct kvm_regs) / sizeof(u32);
}