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

/* Variables and functions */
 struct cam_device* cam_lookup_pass (char const*,int,int,int /*<<< orphan*/ *,struct cam_device*) ; 

struct cam_device *
cam_open_spec_device(const char *dev_name, int unit, int flags,
		     struct cam_device *device)
{
	return(cam_lookup_pass(dev_name, unit, flags, NULL, device));
}