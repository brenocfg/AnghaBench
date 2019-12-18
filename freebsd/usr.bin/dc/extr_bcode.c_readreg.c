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
struct TYPE_2__ {unsigned int reg_array_size; scalar_t__ extended_regs; } ;

/* Variables and functions */
 int EOF ; 
 int UCHAR_MAX ; 
 TYPE_1__ bmachine ; 
 int readch () ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
readreg(void)
{
	int ch1, ch2, idx;

	idx = readch();
	if (idx == 0xff && bmachine.extended_regs) {
		ch1 = readch();
		ch2 = readch();
		if (ch1 == EOF || ch2 == EOF) {
			warnx("unexpected eof");
			idx = -1;
		} else
			idx = (ch1 << 8) + ch2 + UCHAR_MAX + 1;
	}
	if (idx < 0 || (unsigned)idx >= bmachine.reg_array_size) {
		warnx("internal error: reg num = %d", idx);
		idx = -1;
	}
	return (idx);
}