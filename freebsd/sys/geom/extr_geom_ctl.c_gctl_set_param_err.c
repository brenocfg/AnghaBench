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
struct gctl_req {int dummy; } ;

/* Variables and functions */
#define  EINVAL 130 
#define  ENOSPC 129 
#define  EPERM 128 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,char const*) ; 
 int gctl_set_param (struct gctl_req*,char const*,void const*,int) ; 

void
gctl_set_param_err(struct gctl_req *req, const char *param, void const *ptr,
    int len)
{

	switch (gctl_set_param(req, param, ptr, len)) {
	case EPERM:
		gctl_error(req, "No write access %s argument", param);
		break;
	case ENOSPC:
		gctl_error(req, "Wrong length %s argument", param);
		break;
	case EINVAL:
		gctl_error(req, "Missing %s argument", param);
		break;
	}
}