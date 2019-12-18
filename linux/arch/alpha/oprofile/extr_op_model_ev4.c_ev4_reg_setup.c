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
struct op_system_config {int dummy; } ;
struct op_register_config {unsigned long mux_select; scalar_t__ need_reset; scalar_t__ reset_values; scalar_t__ freq; scalar_t__ proc_mode; } ;
struct op_counter_config {int event; unsigned long count; scalar_t__ enabled; } ;

/* Variables and functions */

__attribute__((used)) static void
ev4_reg_setup(struct op_register_config *reg,
	      struct op_counter_config *ctr,
	      struct op_system_config *sys)
{
	unsigned long ctl = 0, count, hilo;

	/* Select desired events.  We've mapped the event numbers
	   such that they fit directly into the event selection fields.

	   Note that there is no "off" setting.  In both cases we select
	   the EXTERNAL event source, hoping that it'll be the lowest
	   frequency, and set the frequency counter to LOW.  The interrupts
	   for these "disabled" counter overflows are ignored by the
	   interrupt handler.

	   This is most irritating, because the hardware *can* enable and
	   disable the interrupts for these counters independently, but the
	   wrperfmon interface doesn't allow it.  */

	ctl |= (ctr[0].enabled ? ctr[0].event << 8 : 14 << 8);
	ctl |= (ctr[1].enabled ? (ctr[1].event - 16) << 32 : 7ul << 32);

	/* EV4 can not read or write its counter registers.  The only
	   thing one can do at all is see if you overflow and get an
	   interrupt.  We can set the width of the counters, to some
	   extent.  Take the interrupt count selected by the user,
	   map it onto one of the possible values, and write it back.  */

	count = ctr[0].count;
	if (count <= 4096)
		count = 4096, hilo = 1;
	else
		count = 65536, hilo = 0;
	ctr[0].count = count;
	ctl |= (ctr[0].enabled && hilo) << 3;

	count = ctr[1].count;
	if (count <= 256)
		count = 256, hilo = 1;
	else
		count = 4096, hilo = 0;
	ctr[1].count = count;
	ctl |= (ctr[1].enabled && hilo);

	reg->mux_select = ctl;

	/* Select performance monitoring options.  */
	/* ??? Need to come up with some mechanism to trace only
	   selected processes.  EV4 does not have a mechanism to
	   select kernel or user mode only.  For now, enable always.  */
	reg->proc_mode = 0;

	/* Frequency is folded into mux_select for EV4.  */
	reg->freq = 0;

	/* See above regarding no writes.  */
	reg->reset_values = 0;
	reg->need_reset = 0;

}