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
struct TYPE_2__ {int addr; int eax; scalar_t__ ctl; } ;

/* Variables and functions */
 int KEYBUFSZ ; 
 int* keybuf ; 
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 
 scalar_t__ vidc_ischar () ; 

__attribute__((used)) static int
vidc_getchar(void)
{
	int i, c;

	for (i = 0; i < KEYBUFSZ; i++) {
		if (keybuf[i] != 0) {
			c = keybuf[i];
			keybuf[i] = 0;
			return (c);
		}
	}

	if (vidc_ischar()) {
		v86.ctl = 0;
		v86.addr = 0x16;
		v86.eax = 0x0;
		v86int();
		if ((v86.eax & 0xff) != 0) {
			return (v86.eax & 0xff);
		}

		/* extended keys */
		switch (v86.eax & 0xff00) {
		case 0x4800:	/* up */
			keybuf[0] = '[';
			keybuf[1] = 'A';
			return (0x1b);	/* esc */
		case 0x4b00:	/* left */
			keybuf[0] = '[';
			keybuf[1] = 'D';
			return (0x1b);	/* esc */
		case 0x4d00:	/* right */
			keybuf[0] = '[';
			keybuf[1] = 'C';
			return (0x1b);	/* esc */
		case 0x5000:	/* down */
			keybuf[0] = '[';
			keybuf[1] = 'B';
			return (0x1b);	/* esc */
		default:
			return (-1);
		}
	} else {
		return (-1);
	}
}