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
typedef  int u8 ;
typedef  int u32 ;
struct pre_div {int pre_div_shift; int /*<<< orphan*/  pre_div_width; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 pre_div_to_ns(struct pre_div *p, u8 pre_div, u32 ns)
{
	u32 mask;

	mask = BIT(p->pre_div_width) - 1;
	mask <<= p->pre_div_shift;
	ns &= ~mask;

	ns |= pre_div << p->pre_div_shift;
	return ns;
}