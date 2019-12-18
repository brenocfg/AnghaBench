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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_REG ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPF_REG_5 ; 
 int /*<<< orphan*/  BPF_REG_7 ; 
 int /*<<< orphan*/  BPF_REG_8 ; 
 int /*<<< orphan*/  BPF_REG_9 ; 
 int /*<<< orphan*/  BPF_REG_AX ; 

__attribute__((used)) static bool is_ereg(u32 reg)
{
	return (1 << reg) & (BIT(BPF_REG_5) |
			     BIT(AUX_REG) |
			     BIT(BPF_REG_7) |
			     BIT(BPF_REG_8) |
			     BIT(BPF_REG_9) |
			     BIT(BPF_REG_AX));
}