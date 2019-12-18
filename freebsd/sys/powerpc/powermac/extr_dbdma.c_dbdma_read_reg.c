#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ sc_off; int /*<<< orphan*/  sc_regs; } ;
typedef  TYPE_1__ dbdma_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uint32_t
dbdma_read_reg(dbdma_channel_t *chan, u_int offset)
{

	return (bus_read_4(chan->sc_regs, chan->sc_off + offset));
}