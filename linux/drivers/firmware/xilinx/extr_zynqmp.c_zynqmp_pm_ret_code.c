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
typedef  int u32 ;

/* Variables and functions */
 int EACCES ; 
 int ECANCELED ; 
 int EINVAL ; 
#define  XST_PM_ABORT_SUSPEND 134 
#define  XST_PM_CONFLICT 133 
#define  XST_PM_DOUBLE_REQ 132 
#define  XST_PM_INTERNAL 131 
#define  XST_PM_INVALID_NODE 130 
#define  XST_PM_NO_ACCESS 129 
#define  XST_PM_SUCCESS 128 

__attribute__((used)) static int zynqmp_pm_ret_code(u32 ret_status)
{
	switch (ret_status) {
	case XST_PM_SUCCESS:
	case XST_PM_DOUBLE_REQ:
		return 0;
	case XST_PM_NO_ACCESS:
		return -EACCES;
	case XST_PM_ABORT_SUSPEND:
		return -ECANCELED;
	case XST_PM_INTERNAL:
	case XST_PM_CONFLICT:
	case XST_PM_INVALID_NODE:
	default:
		return -EINVAL;
	}
}