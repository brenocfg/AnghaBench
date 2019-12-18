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
struct cam_device {int dummy; } ;
typedef  size_t camcontrol_devtype ;

/* Variables and functions */
 unsigned int CC_DT_UNKNOWN ; 
 char** devtype_names ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_device_type (struct cam_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
getdevtype(struct cam_device *cam_dev)
{
	camcontrol_devtype dt;
	int error;

	/*
	 * Get the device type and report it, request no I/O be done to do this.
	 */
	error = get_device_type(cam_dev, -1, 0, 0, &dt);
	if (error != 0 || (unsigned)dt > CC_DT_UNKNOWN) {
		fprintf(stdout, "illegal\n");
		return (1);
	}
	fprintf(stdout, "%s\n", devtype_names[dt]);
	return (0);
}