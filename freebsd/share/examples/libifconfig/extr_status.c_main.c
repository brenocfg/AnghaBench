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
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  ifconfig_close (int /*<<< orphan*/ *) ; 
 scalar_t__ ifconfig_foreach_iface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ifconfig_open () ; 
 int /*<<< orphan*/  print_iface ; 

int
main(int argc, char *argv[])
{
	ifconfig_handle_t *lifh;

	if (argc != 1) {
		errx(1, "Usage: example_status");
	}

	lifh = ifconfig_open();
	if (lifh == NULL) {
		errx(1, "Failed to open libifconfig handle.");
	}

	if (ifconfig_foreach_iface(lifh, print_iface, NULL) != 0) {
		err(1, "Failed to get interfaces");
	}

	ifconfig_close(lifh);
	lifh = NULL;
	return (-1);
}