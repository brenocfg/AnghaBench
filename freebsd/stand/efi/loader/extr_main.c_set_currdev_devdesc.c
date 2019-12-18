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
struct devdesc {int dummy; } ;

/* Variables and functions */
 char* efi_fmtdev (struct devdesc*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  set_currdev (char const*) ; 

__attribute__((used)) static void
set_currdev_devdesc(struct devdesc *currdev)
{
	const char *devname;

	devname = efi_fmtdev(currdev);
	printf("Setting currdev to %s\n", devname);
	set_currdev(devname);
}