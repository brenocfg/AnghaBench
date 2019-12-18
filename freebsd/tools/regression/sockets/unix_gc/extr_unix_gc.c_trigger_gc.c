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
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ forcegc ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trigger_gc(void)
{
	int s;

	if (forcegc) {
		if ((s = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
			err(-1, "trigger_gc: socket");
		close(s);
	}
	sleep(1);
}