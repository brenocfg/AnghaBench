#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct TYPE_2__ {int rdata_shift; } ;

/* Variables and functions */
 TYPE_1__* at93c ; 
 int /*<<< orphan*/  at93c_cycle_clk (int /*<<< orphan*/ ) ; 
 int at93c_datareg_read () ; 
 int /*<<< orphan*/  at93c_reg_read () ; 

__attribute__((used)) static unsigned int at93c_read_databit(void)
{
	u32 data;

	at93c_cycle_clk(at93c_reg_read());
	data = (at93c_datareg_read() >> at93c->rdata_shift) & 1;
	return data;
}