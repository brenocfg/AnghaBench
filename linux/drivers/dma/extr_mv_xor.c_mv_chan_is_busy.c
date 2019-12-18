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
struct mv_xor_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XOR_ACTIVATION (struct mv_xor_chan*) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char mv_chan_is_busy(struct mv_xor_chan *chan)
{
	u32 state = readl_relaxed(XOR_ACTIVATION(chan));

	state = (state >> 4) & 0x3;

	return (state == 1) ? 1 : 0;
}