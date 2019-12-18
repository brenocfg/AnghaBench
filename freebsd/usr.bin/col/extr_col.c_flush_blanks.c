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
 char ESC ; 
 char FHLF ; 
 int /*<<< orphan*/  PUTC (char) ; 
 scalar_t__ fine ; 
 int nblank_lines ; 

__attribute__((used)) static void
flush_blanks(void)
{
	int half, i, nb;

	half = 0;
	nb = nblank_lines;
	if (nb & 1) {
		if (fine)
			half = 1;
		else
			nb++;
	}
	nb /= 2;
	for (i = nb; --i >= 0;)
		PUTC('\n');
	if (half) {
		PUTC(ESC);
		PUTC(FHLF);
		if (!nb)
			PUTC('\r');
	}
	nblank_lines = 0;
}