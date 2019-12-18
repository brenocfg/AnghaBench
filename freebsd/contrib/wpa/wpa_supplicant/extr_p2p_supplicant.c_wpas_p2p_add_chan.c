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
typedef  int /*<<< orphan*/  u8 ;
struct p2p_reg_class {size_t channels; int /*<<< orphan*/ * channel; } ;

/* Variables and functions */

__attribute__((used)) static void wpas_p2p_add_chan(struct p2p_reg_class *reg, u8 chan)
{
	reg->channel[reg->channels] = chan;
	reg->channels++;
}