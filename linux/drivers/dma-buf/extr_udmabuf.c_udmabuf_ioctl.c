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
struct file {int dummy; } ;

/* Variables and functions */
 long ENOTTY ; 
#define  UDMABUF_CREATE 129 
#define  UDMABUF_CREATE_LIST 128 
 long udmabuf_ioctl_create (struct file*,unsigned long) ; 
 long udmabuf_ioctl_create_list (struct file*,unsigned long) ; 

__attribute__((used)) static long udmabuf_ioctl(struct file *filp, unsigned int ioctl,
			  unsigned long arg)
{
	long ret;

	switch (ioctl) {
	case UDMABUF_CREATE:
		ret = udmabuf_ioctl_create(filp, arg);
		break;
	case UDMABUF_CREATE_LIST:
		ret = udmabuf_ioctl_create_list(filp, arg);
		break;
	default:
		ret = -ENOTTY;
		break;
	}
	return ret;
}