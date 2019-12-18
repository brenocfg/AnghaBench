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
typedef  int /*<<< orphan*/  dev_name ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_IDLEN ; 
 int cam_get_device (char const*,char*,int,int*) ; 
 struct cam_device* cam_lookup_pass (char*,int,int,char const*,int /*<<< orphan*/ *) ; 

struct cam_device *
cam_open_device(const char *path, int flags)
{
	int unit;
	char dev_name[DEV_IDLEN + 1];

	/*
	 * cam_get_device() has already put an error message in cam_errbuf,
	 * so we don't need to.
	 */
	if (cam_get_device(path, dev_name, sizeof(dev_name), &unit) == -1)
		return(NULL);

	return(cam_lookup_pass(dev_name, unit, flags, path, NULL));
}