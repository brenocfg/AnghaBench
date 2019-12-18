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
struct pf_status {int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETSTATUS ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pf_status*) ; 
 int /*<<< orphan*/  print_running (struct pf_status*) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
pfctl_show_running(int dev)
{
	struct pf_status status;

	if (ioctl(dev, DIOCGETSTATUS, &status)) {
		warn("DIOCGETSTATUS");
		return (-1);
	}

	print_running(&status);
	return (!status.running);
}