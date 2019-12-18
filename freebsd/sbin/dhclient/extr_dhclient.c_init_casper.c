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
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  cap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cap_init () ; 
 int /*<<< orphan*/ * cap_service_open (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * capsyslog ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static void
init_casper(void)
{
	cap_channel_t		*casper;

	casper = cap_init();
	if (casper == NULL)
		error("unable to start casper");

	capsyslog = cap_service_open(casper, "system.syslog");
	cap_close(casper);
	if (capsyslog == NULL)
		error("unable to open system.syslog service");
}