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
 int EOF ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errf (char*) ; 
 int scanc () ; 

void
scan_to_eol(void)
{
	int	c;
	while ((c = scanc()) != '\n') {
		if (c == EOF) {
			/* end of file without newline! */
			errf("missing newline");
			return;
		}
	}
	assert(c == '\n');
}