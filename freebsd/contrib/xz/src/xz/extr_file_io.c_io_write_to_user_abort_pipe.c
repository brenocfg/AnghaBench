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
typedef  char uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/ * user_abort_pipe ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

extern void
io_write_to_user_abort_pipe(void)
{
	// If the write() fails, it's probably due to the pipe being full.
	// Failing in that case is fine. If the reason is something else,
	// there's not much we can do since this is called in a signal
	// handler. So ignore the errors and try to avoid warnings with
	// GCC and glibc when _FORTIFY_SOURCE=2 is used.
	uint8_t b = '\0';
	const int ret = write(user_abort_pipe[1], &b, 1);
	(void)ret;
	return;
}