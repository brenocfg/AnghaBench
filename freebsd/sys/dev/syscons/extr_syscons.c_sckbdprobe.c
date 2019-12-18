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
 int /*<<< orphan*/  KB_CONF_PROBE_ONLY ; 
 int /*<<< orphan*/  kbd_configure (int /*<<< orphan*/ ) ; 
 scalar_t__ kbd_find_keyboard (char*,int) ; 

__attribute__((used)) static int
sckbdprobe(int unit, int flags, int cons)
{
    /* access the keyboard driver through the backdoor! */
    kbd_configure(cons ? KB_CONF_PROBE_ONLY : 0);

    return (kbd_find_keyboard("*", unit) >= 0);
}