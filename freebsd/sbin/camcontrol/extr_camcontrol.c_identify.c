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
struct ccb_pathinq {scalar_t__ protocol; } ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ PROTO_NVME ; 
 int ataidentify (struct cam_device*,int,int) ; 
 scalar_t__ get_cpi (struct cam_device*,struct ccb_pathinq*) ; 
 int nvmeidentify (struct cam_device*,int,int) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
identify(struct cam_device *device, int retry_count, int timeout)
{
#ifdef WITH_NVME
	struct ccb_pathinq cpi;

	if (get_cpi(device, &cpi) != 0) {
		warnx("couldn't get CPI");
		return (-1);
	}

	if (cpi.protocol == PROTO_NVME) {
		return (nvmeidentify(device, retry_count, timeout));
	}
#endif
	return (ataidentify(device, retry_count, timeout));
}