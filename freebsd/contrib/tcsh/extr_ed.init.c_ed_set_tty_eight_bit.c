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
 int /*<<< orphan*/  SHTTY ; 
 int /*<<< orphan*/  Tty_eight_bit ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  extty ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_geteightbit (int /*<<< orphan*/ *) ; 
 int tty_getty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

void
ed_set_tty_eight_bit(void)
{
    if (tty_getty(SHTTY, &extty) == -1) {
#ifdef DEBUG_TTY
	xprintf("ed_set_tty_eight_bit: tty_getty: %s\n", strerror(errno));
#endif /* DEBUG_TTY */
	return;
    }
    Tty_eight_bit = tty_geteightbit(&extty);
}