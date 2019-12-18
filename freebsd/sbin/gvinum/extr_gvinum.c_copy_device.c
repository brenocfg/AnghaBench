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
struct gv_drive {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static void
copy_device(struct gv_drive *d, const char *device)
{

	if (strncmp(device, "/dev/", 5) == 0)
		strlcpy(d->device, (device + 5), sizeof(d->device));
	else
		strlcpy(d->device, device, sizeof(d->device));
}