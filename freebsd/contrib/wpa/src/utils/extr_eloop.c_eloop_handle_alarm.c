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
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eloop_handle_alarm(int sig)
{
	wpa_printf(MSG_ERROR, "eloop: could not process SIGINT or SIGTERM in "
		   "two seconds. Looks like there\n"
		   "is a bug that ends up in a busy loop that "
		   "prevents clean shutdown.\n"
		   "Killing program forcefully.\n");
	exit(1);
}