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
struct i40e_hw {char const* err_str; } ;
typedef  enum i40e_admin_queue_err { ____Placeholder_i40e_admin_queue_err } i40e_admin_queue_err ;

/* Variables and functions */
#define  I40E_AQ_RC_BAD_ADDR 150 
#define  I40E_AQ_RC_E2BIG 149 
#define  I40E_AQ_RC_EACCES 148 
#define  I40E_AQ_RC_EAGAIN 147 
#define  I40E_AQ_RC_EBUSY 146 
#define  I40E_AQ_RC_EEXIST 145 
#define  I40E_AQ_RC_EFAULT 144 
#define  I40E_AQ_RC_EFBIG 143 
#define  I40E_AQ_RC_EFLUSHED 142 
#define  I40E_AQ_RC_EINTR 141 
#define  I40E_AQ_RC_EINVAL 140 
#define  I40E_AQ_RC_EIO 139 
#define  I40E_AQ_RC_EMODE 138 
#define  I40E_AQ_RC_ENOENT 137 
#define  I40E_AQ_RC_ENOMEM 136 
#define  I40E_AQ_RC_ENOSPC 135 
#define  I40E_AQ_RC_ENOSYS 134 
#define  I40E_AQ_RC_ENOTTY 133 
#define  I40E_AQ_RC_ENXIO 132 
#define  I40E_AQ_RC_EPERM 131 
#define  I40E_AQ_RC_ERANGE 130 
#define  I40E_AQ_RC_ESRCH 129 
#define  I40E_AQ_RC_OK 128 
 int /*<<< orphan*/  snprintf (char const*,int,char*,int) ; 

const char *i40e_aq_str(struct i40e_hw *hw, enum i40e_admin_queue_err aq_err)
{
	switch (aq_err) {
	case I40E_AQ_RC_OK:
		return "OK";
	case I40E_AQ_RC_EPERM:
		return "I40E_AQ_RC_EPERM";
	case I40E_AQ_RC_ENOENT:
		return "I40E_AQ_RC_ENOENT";
	case I40E_AQ_RC_ESRCH:
		return "I40E_AQ_RC_ESRCH";
	case I40E_AQ_RC_EINTR:
		return "I40E_AQ_RC_EINTR";
	case I40E_AQ_RC_EIO:
		return "I40E_AQ_RC_EIO";
	case I40E_AQ_RC_ENXIO:
		return "I40E_AQ_RC_ENXIO";
	case I40E_AQ_RC_E2BIG:
		return "I40E_AQ_RC_E2BIG";
	case I40E_AQ_RC_EAGAIN:
		return "I40E_AQ_RC_EAGAIN";
	case I40E_AQ_RC_ENOMEM:
		return "I40E_AQ_RC_ENOMEM";
	case I40E_AQ_RC_EACCES:
		return "I40E_AQ_RC_EACCES";
	case I40E_AQ_RC_EFAULT:
		return "I40E_AQ_RC_EFAULT";
	case I40E_AQ_RC_EBUSY:
		return "I40E_AQ_RC_EBUSY";
	case I40E_AQ_RC_EEXIST:
		return "I40E_AQ_RC_EEXIST";
	case I40E_AQ_RC_EINVAL:
		return "I40E_AQ_RC_EINVAL";
	case I40E_AQ_RC_ENOTTY:
		return "I40E_AQ_RC_ENOTTY";
	case I40E_AQ_RC_ENOSPC:
		return "I40E_AQ_RC_ENOSPC";
	case I40E_AQ_RC_ENOSYS:
		return "I40E_AQ_RC_ENOSYS";
	case I40E_AQ_RC_ERANGE:
		return "I40E_AQ_RC_ERANGE";
	case I40E_AQ_RC_EFLUSHED:
		return "I40E_AQ_RC_EFLUSHED";
	case I40E_AQ_RC_BAD_ADDR:
		return "I40E_AQ_RC_BAD_ADDR";
	case I40E_AQ_RC_EMODE:
		return "I40E_AQ_RC_EMODE";
	case I40E_AQ_RC_EFBIG:
		return "I40E_AQ_RC_EFBIG";
	}

	snprintf(hw->err_str, sizeof(hw->err_str), "%d", aq_err);
	return hw->err_str;
}