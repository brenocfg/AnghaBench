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
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENXIO ; 
 int EWOULDBLOCK ; 
 int SMB_EABORT ; 
 int SMB_EBUSERR ; 
 int SMB_EBUSY ; 
 int SMB_ECOLLI ; 
 int SMB_ENOACK ; 
 int SMB_ENOERR ; 
 int SMB_ENOTSUPP ; 
 int SMB_ETIMEOUT ; 

int
smbus_error(int smb_error)
{
	int error = 0;

	if (smb_error == SMB_ENOERR)
		return (0);
	
	if (smb_error & (SMB_ENOTSUPP))
		error = ENODEV;
	else if (smb_error & (SMB_ENOACK))
		error = ENXIO;
	else if (smb_error & (SMB_ETIMEOUT))
		error = EWOULDBLOCK;
	else if (smb_error & (SMB_EBUSY))
		error = EBUSY;
	else if (smb_error & (SMB_EABORT | SMB_EBUSERR | SMB_ECOLLI))
		error = EIO;
	else
		error = EINVAL;

	return (error);
}