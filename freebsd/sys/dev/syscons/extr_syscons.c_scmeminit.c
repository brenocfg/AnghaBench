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
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VTY_SC ; 
 int /*<<< orphan*/  sc_alloc_cut_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_alloc_history_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_alloc_scr_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_console ; 
 scalar_t__ sc_console_unit ; 
 scalar_t__ sc_malloc ; 
 int /*<<< orphan*/  vty_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scmeminit(void *arg)
{
    if (!vty_enabled(VTY_SC))
        return;
    if (sc_malloc)
	return;
    sc_malloc = TRUE;

    /*
     * As soon as malloc() becomes functional, we had better allocate
     * various buffers for the kernel console.
     */

    if (sc_console_unit < 0)	/* sc_console == NULL */
	return;

    /* copy the temporary buffer to the final buffer */
    sc_alloc_scr_buffer(sc_console, FALSE, FALSE);

#ifndef SC_NO_CUTPASTE
    sc_alloc_cut_buffer(sc_console, FALSE);
#endif

#ifndef SC_NO_HISTORY
    /* initialize history buffer & pointers */
    sc_alloc_history_buffer(sc_console, 0, 0, FALSE);
#endif
}