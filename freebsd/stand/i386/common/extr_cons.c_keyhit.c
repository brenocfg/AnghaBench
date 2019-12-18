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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ OPT_CHECK (int /*<<< orphan*/ ) ; 
 scalar_t__ PTOV (int) ; 
 int /*<<< orphan*/  RBX_NOINTR ; 
 unsigned int SECOND ; 
 int xgetc (int) ; 

int
keyhit(unsigned int secs)
{
	uint32_t t0, t1, c;

	if (OPT_CHECK(RBX_NOINTR))
		return (0);
	secs *= SECOND;
	t0 = 0;
	for (;;) {
		/*
		 * The extra comparison is an attempt to work around
		 * what appears to be a bug in QEMU and Bochs. Both emulators
		 * sometimes report a key-press with scancode one and ascii zero
		 * when no such key is pressed in reality. As far as I can tell,
		 * this only happens shortly after a reboot.
		 */
		c = xgetc(1);
		if (c != 0 && c != 0x0100)
			return (1);
		if (secs > 0) {
			t1 = *(uint32_t *)PTOV(0x46c);
			if (!t0)
				t0 = t1;
			if (t1 < t0 || t1 >= t0 + secs)
				return (0);
		}
	}
	/* NOTREACHED */
}