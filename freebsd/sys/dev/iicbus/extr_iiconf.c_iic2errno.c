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
 int EADDRNOTAVAIL ; 
 int EALREADY ; 
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EOVERFLOW ; 
 int EPROTO ; 
 int ETIMEDOUT ; 
 int EWOULDBLOCK ; 
#define  IIC_EBUSBSY 138 
#define  IIC_EBUSERR 137 
#define  IIC_ENOACK 136 
#define  IIC_ENOADDR 135 
#define  IIC_ENOTSUPP 134 
#define  IIC_EOVERFLOW 133 
#define  IIC_ERESOURCE 132 
 int IIC_ERRNO ; 
#define  IIC_ESTATUS 131 
#define  IIC_ETIMEOUT 130 
#define  IIC_EUNDERFLOW 129 
#define  IIC_NOERR 128 

int
iic2errno(int iic_status)
{
	switch (iic_status) {
	case IIC_NOERR:         return (0);
	case IIC_EBUSERR:       return (EALREADY);
	case IIC_ENOACK:        return (EIO);
	case IIC_ETIMEOUT:      return (ETIMEDOUT);
	case IIC_EBUSBSY:       return (EWOULDBLOCK);
	case IIC_ESTATUS:       return (EPROTO);
	case IIC_EUNDERFLOW:    return (EIO);
	case IIC_EOVERFLOW:     return (EOVERFLOW);
	case IIC_ENOTSUPP:      return (EOPNOTSUPP);
	case IIC_ENOADDR:       return (EADDRNOTAVAIL);
	case IIC_ERESOURCE:     return (ENOMEM);
	default:
		/*
		 * If the high bit is set, that means it's a system errno value
		 * that was encoded into the IIC_Exxxxxx space by setting the
		 * IIC_ERRNO marker bit.  If lots of high-order bits are set,
		 * then it's one of the negative pseudo-errors such as ERESTART
		 * and we return it as-is.  Otherwise it's a plain "small
		 * positive integer" errno, so just remove the IIC_ERRNO marker
		 * bit.  If it's some unknown number without the high bit set,
		 * there isn't much we can do except call it an I/O error.
		 */
		if ((iic_status & IIC_ERRNO) == 0)
			return (EIO);
		if ((iic_status & 0xFFFF0000) != 0)
			return (iic_status);
		return (iic_status & ~IIC_ERRNO);
	}
}