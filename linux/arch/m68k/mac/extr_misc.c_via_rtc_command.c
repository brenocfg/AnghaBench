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
typedef  int __u8 ;

/* Variables and functions */
 int RTC_FLG_READ ; 
 int VIA1B_vRTCClk ; 
 int VIA1B_vRTCEnb ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 size_t vBufB ; 
 int* via1 ; 
 int via_rtc_recv () ; 
 int /*<<< orphan*/  via_rtc_send (int) ; 

__attribute__((used)) static void via_rtc_command(int command, __u8 *data)
{
	unsigned long flags;
	int is_read;

	local_irq_save(flags);

	/* The least significant bits must be 0b01 according to Inside Mac */

	command = (command & ~3) | 1;

	/* Enable the RTC and make sure the strobe line is high */

	via1[vBufB] = (via1[vBufB] | VIA1B_vRTCClk) & ~VIA1B_vRTCEnb;

	if (command & 0xFF00) {		/* extended (two-byte) command */
		via_rtc_send((command & 0xFF00) >> 8);
		via_rtc_send(command & 0xFF);
		is_read = command & (RTC_FLG_READ << 8);
	} else {			/* one-byte command */
		via_rtc_send(command);
		is_read = command & RTC_FLG_READ;
	}
	if (is_read) {
		*data = via_rtc_recv();
	} else {
		via_rtc_send(*data);
	}

	/* All done, disable the RTC */

	via1[vBufB] |= VIA1B_vRTCEnb;

	local_irq_restore(flags);
}