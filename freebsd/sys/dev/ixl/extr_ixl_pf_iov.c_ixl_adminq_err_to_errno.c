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
typedef  enum i40e_admin_queue_err { ____Placeholder_i40e_admin_queue_err } i40e_admin_queue_err ;

/* Variables and functions */
 int E2BIG ; 
 int EACCES ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EEXIST ; 
 int EFAULT ; 
 int EFBIG ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENOSYS ; 
 int ENOTTY ; 
 int ENXIO ; 
 int EPERM ; 
 int ERANGE ; 
 int ESRCH ; 
#define  I40E_AQ_RC_BAD_ADDR 149 
#define  I40E_AQ_RC_E2BIG 148 
#define  I40E_AQ_RC_EACCES 147 
#define  I40E_AQ_RC_EAGAIN 146 
#define  I40E_AQ_RC_EBUSY 145 
#define  I40E_AQ_RC_EEXIST 144 
#define  I40E_AQ_RC_EFAULT 143 
#define  I40E_AQ_RC_EFBIG 142 
#define  I40E_AQ_RC_EFLUSHED 141 
#define  I40E_AQ_RC_EINTR 140 
#define  I40E_AQ_RC_EINVAL 139 
#define  I40E_AQ_RC_EIO 138 
#define  I40E_AQ_RC_EMODE 137 
#define  I40E_AQ_RC_ENOENT 136 
#define  I40E_AQ_RC_ENOMEM 135 
#define  I40E_AQ_RC_ENOSPC 134 
#define  I40E_AQ_RC_ENOSYS 133 
#define  I40E_AQ_RC_ENOTTY 132 
#define  I40E_AQ_RC_ENXIO 131 
#define  I40E_AQ_RC_EPERM 130 
#define  I40E_AQ_RC_ERANGE 129 
#define  I40E_AQ_RC_ESRCH 128 

__attribute__((used)) static int
ixl_adminq_err_to_errno(enum i40e_admin_queue_err err)
{

	switch (err) {
	case I40E_AQ_RC_EPERM:
		return (EPERM);
	case I40E_AQ_RC_ENOENT:
		return (ENOENT);
	case I40E_AQ_RC_ESRCH:
		return (ESRCH);
	case I40E_AQ_RC_EINTR:
		return (EINTR);
	case I40E_AQ_RC_EIO:
		return (EIO);
	case I40E_AQ_RC_ENXIO:
		return (ENXIO);
	case I40E_AQ_RC_E2BIG:
		return (E2BIG);
	case I40E_AQ_RC_EAGAIN:
		return (EAGAIN);
	case I40E_AQ_RC_ENOMEM:
		return (ENOMEM);
	case I40E_AQ_RC_EACCES:
		return (EACCES);
	case I40E_AQ_RC_EFAULT:
		return (EFAULT);
	case I40E_AQ_RC_EBUSY:
		return (EBUSY);
	case I40E_AQ_RC_EEXIST:
		return (EEXIST);
	case I40E_AQ_RC_EINVAL:
		return (EINVAL);
	case I40E_AQ_RC_ENOTTY:
		return (ENOTTY);
	case I40E_AQ_RC_ENOSPC:
		return (ENOSPC);
	case I40E_AQ_RC_ENOSYS:
		return (ENOSYS);
	case I40E_AQ_RC_ERANGE:
		return (ERANGE);
	case I40E_AQ_RC_EFLUSHED:
		return (EINVAL);	/* No exact equivalent in errno.h */
	case I40E_AQ_RC_BAD_ADDR:
		return (EFAULT);
	case I40E_AQ_RC_EMODE:
		return (EPERM);
	case I40E_AQ_RC_EFBIG:
		return (EFBIG);
	default:
		return (EINVAL);
	}
}