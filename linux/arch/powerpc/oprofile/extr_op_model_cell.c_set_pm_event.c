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
typedef  size_t u32 ;
struct pm_signal {int signal_group; int bus_word; size_t bit; scalar_t__ sub_unit; } ;
struct TYPE_2__ {size_t debug_bus_control; int group_control; int /*<<< orphan*/ * pm07_cntrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBE_COUNT_ALL_CYCLES ; 
 size_t GET_BUS_TYPE (size_t) ; 
 size_t GET_BUS_WORD (size_t) ; 
 size_t GET_COUNT_CYCLES (size_t) ; 
 size_t GET_INPUT_CONTROL (size_t) ; 
 size_t GET_POLARITY (size_t) ; 
 scalar_t__ GET_SUB_UNIT (size_t) ; 
 int NUM_DEBUG_BUS_WORDS ; 
 int NUM_INPUT_BUS_WORDS ; 
 int /*<<< orphan*/  PM07_CTR_COUNT_CYCLES (size_t) ; 
 int /*<<< orphan*/  PM07_CTR_INPUT_CONTROL (size_t) ; 
 int /*<<< orphan*/  PM07_CTR_INPUT_MUX (size_t) ; 
 int /*<<< orphan*/  PM07_CTR_POLARITY (size_t) ; 
 int PPU_CYCLES_EVENT_NUM ; 
 int PPU_CYCLES_GRP_NUM ; 
 int* input_bus ; 
 TYPE_1__ pm_regs ; 
 struct pm_signal* pm_signal ; 

__attribute__((used)) static void set_pm_event(u32 ctr, int event, u32 unit_mask)
{
	struct pm_signal *p;
	u32 signal_bit;
	u32 bus_word, bus_type, count_cycles, polarity, input_control;
	int j, i;

	if (event == PPU_CYCLES_EVENT_NUM) {
		/* Special Event: Count all cpu cycles */
		pm_regs.pm07_cntrl[ctr] = CBE_COUNT_ALL_CYCLES;
		p = &(pm_signal[ctr]);
		p->signal_group = PPU_CYCLES_GRP_NUM;
		p->bus_word = 1;
		p->sub_unit = 0;
		p->bit = 0;
		goto out;
	} else {
		pm_regs.pm07_cntrl[ctr] = 0;
	}

	bus_word = GET_BUS_WORD(unit_mask);
	bus_type = GET_BUS_TYPE(unit_mask);
	count_cycles = GET_COUNT_CYCLES(unit_mask);
	polarity = GET_POLARITY(unit_mask);
	input_control = GET_INPUT_CONTROL(unit_mask);
	signal_bit = (event % 100);

	p = &(pm_signal[ctr]);

	p->signal_group = event / 100;
	p->bus_word = bus_word;
	p->sub_unit = GET_SUB_UNIT(unit_mask);

	pm_regs.pm07_cntrl[ctr] = 0;
	pm_regs.pm07_cntrl[ctr] |= PM07_CTR_COUNT_CYCLES(count_cycles);
	pm_regs.pm07_cntrl[ctr] |= PM07_CTR_POLARITY(polarity);
	pm_regs.pm07_cntrl[ctr] |= PM07_CTR_INPUT_CONTROL(input_control);

	/*
	 * Some of the islands signal selection is based on 64 bit words.
	 * The debug bus words are 32 bits, the input words to the performance
	 * counters are defined as 32 bits.  Need to convert the 64 bit island
	 * specification to the appropriate 32 input bit and bus word for the
	 * performance counter event selection.	 See the CELL Performance
	 * monitoring signals manual and the Perf cntr hardware descriptions
	 * for the details.
	 */
	if (input_control == 0) {
		if (signal_bit > 31) {
			signal_bit -= 32;
			if (bus_word == 0x3)
				bus_word = 0x2;
			else if (bus_word == 0xc)
				bus_word = 0x8;
		}

		if ((bus_type == 0) && p->signal_group >= 60)
			bus_type = 2;
		if ((bus_type == 1) && p->signal_group >= 50)
			bus_type = 0;

		pm_regs.pm07_cntrl[ctr] |= PM07_CTR_INPUT_MUX(signal_bit);
	} else {
		pm_regs.pm07_cntrl[ctr] = 0;
		p->bit = signal_bit;
	}

	for (i = 0; i < NUM_DEBUG_BUS_WORDS; i++) {
		if (bus_word & (1 << i)) {
			pm_regs.debug_bus_control |=
				(bus_type << (30 - (2 * i)));

			for (j = 0; j < NUM_INPUT_BUS_WORDS; j++) {
				if (input_bus[j] == 0xff) {
					input_bus[j] = i;
					pm_regs.group_control |=
						(i << (30 - (2 * j)));

					break;
				}
			}
		}
	}
out:
	;
}