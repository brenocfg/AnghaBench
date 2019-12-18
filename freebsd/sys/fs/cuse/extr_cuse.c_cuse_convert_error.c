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

/* Variables and functions */
#define  CUSE_ERR_BUSY 135 
#define  CUSE_ERR_FAULT 134 
#define  CUSE_ERR_INVALID 133 
#define  CUSE_ERR_NONE 132 
#define  CUSE_ERR_NO_DEVICE 131 
#define  CUSE_ERR_NO_MEMORY 130 
#define  CUSE_ERR_SIGNAL 129 
#define  CUSE_ERR_WOULDBLOCK 128 
 int EBUSY ; 
 int EFAULT ; 
 int EINTR ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EWOULDBLOCK ; 

__attribute__((used)) static int
cuse_convert_error(int error)
{
	;				/* indent fix */
	switch (error) {
	case CUSE_ERR_NONE:
		return (0);
	case CUSE_ERR_BUSY:
		return (EBUSY);
	case CUSE_ERR_WOULDBLOCK:
		return (EWOULDBLOCK);
	case CUSE_ERR_INVALID:
		return (EINVAL);
	case CUSE_ERR_NO_MEMORY:
		return (ENOMEM);
	case CUSE_ERR_FAULT:
		return (EFAULT);
	case CUSE_ERR_SIGNAL:
		return (EINTR);
	case CUSE_ERR_NO_DEVICE:
		return (ENODEV);
	default:
		return (ENXIO);
	}
}