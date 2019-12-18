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
 int /*<<< orphan*/  hostapd_cli_close_connection () ; 
 int /*<<< orphan*/  os_daemonize_terminate (scalar_t__) ; 
 int /*<<< orphan*/  os_program_deinit () ; 
 scalar_t__ pid_file ; 

__attribute__((used)) static void hostapd_cli_cleanup(void)
{
	hostapd_cli_close_connection();
	if (pid_file)
		os_daemonize_terminate(pid_file);

	os_program_deinit();
}