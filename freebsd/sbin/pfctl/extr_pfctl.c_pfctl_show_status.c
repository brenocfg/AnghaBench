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
struct pf_status {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETSTATUS ; 
 int PF_OPT_SHOWALL ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pf_status*) ; 
 int /*<<< orphan*/  pfctl_print_title (char*) ; 
 int /*<<< orphan*/  print_status (struct pf_status*,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
pfctl_show_status(int dev, int opts)
{
	struct pf_status status;

	if (ioctl(dev, DIOCGETSTATUS, &status)) {
		warn("DIOCGETSTATUS");
		return (-1);
	}
	if (opts & PF_OPT_SHOWALL)
		pfctl_print_title("INFO:");
	print_status(&status, opts);
	return (0);
}