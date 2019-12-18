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
struct wrpll_cfg {int flags; } ;

/* Variables and functions */
 int WRPLL_FLAGS_INT_FEEDBACK_MASK ; 

__attribute__((used)) static u8 __wrpll_calc_fbdiv(const struct wrpll_cfg *c)
{
	return (c->flags & WRPLL_FLAGS_INT_FEEDBACK_MASK) ? 2 : 1;
}