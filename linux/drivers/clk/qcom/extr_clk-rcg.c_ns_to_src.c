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
struct src_sel {int src_sel_shift; } ;

/* Variables and functions */
 int SRC_SEL_MASK ; 

__attribute__((used)) static u32 ns_to_src(struct src_sel *s, u32 ns)
{
	ns >>= s->src_sel_shift;
	ns &= SRC_SEL_MASK;
	return ns;
}