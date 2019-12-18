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
struct TYPE_3__ {scalar_t__ ks_inq_length; unsigned char* ks_inq; size_t ks_inq_start; } ;
typedef  TYPE_1__ kbdmux_state_t ;

/* Variables and functions */
 int KBDMUX_Q_SIZE ; 

__attribute__((used)) static int
kbdmux_kbd_getc(kbdmux_state_t *state)
{
	unsigned char c;

	if (state->ks_inq_length == 0)
		return (-1);

	c = state->ks_inq[state->ks_inq_start];
	state->ks_inq_start = (state->ks_inq_start + 1) % KBDMUX_Q_SIZE;
	state->ks_inq_length--;

	return (c);
}