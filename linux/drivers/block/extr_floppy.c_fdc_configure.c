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

/* Variables and functions */
 int FD_CONFIGURE ; 
 scalar_t__ MORE_OUTPUT ; 
 int fifo_depth ; 
 scalar_t__ need_more_output () ; 
 int no_fifo ; 
 int /*<<< orphan*/  output_byte (int) ; 

__attribute__((used)) static int fdc_configure(void)
{
	/* Turn on FIFO */
	output_byte(FD_CONFIGURE);
	if (need_more_output() != MORE_OUTPUT)
		return 0;
	output_byte(0);
	output_byte(0x10 | (no_fifo & 0x20) | (fifo_depth & 0xf));
	output_byte(0);		/* pre-compensation from track
				   0 upwards */
	return 1;
}