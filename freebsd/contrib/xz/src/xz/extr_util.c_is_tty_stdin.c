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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  _ (char*) ; 
 int isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_error (int /*<<< orphan*/ ) ; 

extern bool
is_tty_stdin(void)
{
	const bool ret = isatty(STDIN_FILENO);

	if (ret)
		message_error(_("Compressed data cannot be read from "
				"a terminal"));

	return ret;
}