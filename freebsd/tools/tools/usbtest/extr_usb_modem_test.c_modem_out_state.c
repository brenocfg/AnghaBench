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
typedef  char uint8_t ;
struct TYPE_2__ {int out_state; int /*<<< orphan*/  c0; scalar_t__ modem_at_mode; } ;

/* Variables and functions */
 TYPE_1__ modem ; 

__attribute__((used)) static void
modem_out_state(uint8_t *buf)
{
	if (modem.modem_at_mode) {
		switch (modem.out_state & 3) {
		case 0:
			*buf = 'A';
			break;
		case 1:
			*buf = 'T';
			break;
		case 2:
			*buf = '\r';
			break;
		default:
			*buf = '\n';
			modem.c0++;
			break;
		}
		modem.out_state++;
	} else {
		*buf = modem.out_state;
		modem.out_state++;
		modem.out_state %= 255;
	}
}