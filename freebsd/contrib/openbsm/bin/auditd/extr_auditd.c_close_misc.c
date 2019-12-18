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
 int /*<<< orphan*/  AUDITD_PIDFILE ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  auditd_close_dirs () ; 
 scalar_t__ auditd_close_trigger () ; 
 int /*<<< orphan*/  auditd_log_err (char*,...) ; 
 int /*<<< orphan*/  endac () ; 
 scalar_t__ errno ; 
 int unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
close_misc(void)
{

	auditd_close_dirs();
	if (unlink(AUDITD_PIDFILE) == -1 && errno != ENOENT) {
		auditd_log_err("Couldn't remove %s: %m", AUDITD_PIDFILE);
		return (1);
	}
	endac();

	if (auditd_close_trigger() != 0) {
		auditd_log_err("Error closing trigger messaging mechanism");
		return (1);
	}
	return (0);
}