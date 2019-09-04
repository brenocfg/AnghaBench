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
 int EPIPE ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  async_exit (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ in_async () ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void check_pipe(int err)
{
	if (err == EPIPE) {
		if (in_async())
			async_exit(141);

		signal(SIGPIPE, SIG_DFL);
		raise(SIGPIPE);
		/* Should never happen, but just in case... */
		exit(141);
	}
}