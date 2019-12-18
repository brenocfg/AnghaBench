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
#define  IIC_EBUSBSY 138 
#define  IIC_EBUSERR 137 
#define  IIC_ENOACK 136 
#define  IIC_ENOADDR 135 
#define  IIC_ENOTSUPP 134 
#define  IIC_EOVERFLOW 133 
#define  IIC_ERESOURCE 132 
#define  IIC_ESTATUS 131 
#define  IIC_ETIMEOUT 130 
#define  IIC_EUNDERFLOW 129 
#define  IIC_NOERR 128 
 int SMB_EBUSERR ; 
 int SMB_EBUSY ; 
 int SMB_ENOACK ; 
 int SMB_ENOERR ; 
 int SMB_ENOTSUPP ; 
 int SMB_ETIMEOUT ; 

__attribute__((used)) static int
iic2smb_error(int error)
{
	switch (error) {
	case IIC_NOERR:
		return (SMB_ENOERR);
	case IIC_EBUSERR:
		return (SMB_EBUSERR);
	case IIC_ENOACK:
		return (SMB_ENOACK);
	case IIC_ETIMEOUT:
		return (SMB_ETIMEOUT);
	case IIC_EBUSBSY:
		return (SMB_EBUSY);
	case IIC_ESTATUS:
		return (SMB_EBUSERR);
	case IIC_EUNDERFLOW:
		return (SMB_EBUSERR);
	case IIC_EOVERFLOW:
		return (SMB_EBUSERR);
	case IIC_ENOTSUPP:
		return (SMB_ENOTSUPP);
	case IIC_ENOADDR:
		return (SMB_EBUSERR);
	case IIC_ERESOURCE:
		return (SMB_EBUSERR);
	default:
		return (SMB_EBUSERR);
	}
}