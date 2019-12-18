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
 scalar_t__ background ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  rump_daemonize_done (int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  warnx (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
die(const char *reason, int error)
{

	warnx("%s: %s", reason, strerror(error));
	if (background)
		rump_daemonize_done(error);
	exit(1);
}