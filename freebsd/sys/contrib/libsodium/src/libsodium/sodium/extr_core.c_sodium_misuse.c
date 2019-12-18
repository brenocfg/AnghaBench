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
 void _misuse_handler () ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ sodium_crit_enter () ; 
 int /*<<< orphan*/  sodium_crit_leave () ; 

void
sodium_misuse(void)
{
    void (*handler)(void);

    (void) sodium_crit_leave();
    if (sodium_crit_enter() == 0) {
        handler = _misuse_handler;
        if (handler != NULL) {
            handler();
        }
    }
/* LCOV_EXCL_START */
    abort();
}