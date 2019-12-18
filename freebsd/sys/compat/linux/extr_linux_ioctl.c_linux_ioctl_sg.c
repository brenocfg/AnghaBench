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
struct thread {int dummy; } ;
struct linux_ioctl_args {int cmd; } ;
struct ioctl_args {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
#define  LINUX_SG_GET_RESERVED_SIZE 134 
#define  LINUX_SG_GET_SCSI_ID 133 
#define  LINUX_SG_GET_SG_TABLESIZE 132 
#define  LINUX_SG_GET_TIMEOUT 131 
#define  LINUX_SG_GET_VERSION_NUM 130 
#define  LINUX_SG_IO 129 
#define  LINUX_SG_SET_TIMEOUT 128 
 int SG_GET_RESERVED_SIZE ; 
 int SG_GET_SCSI_ID ; 
 int SG_GET_SG_TABLESIZE ; 
 int SG_GET_TIMEOUT ; 
 int SG_GET_VERSION_NUM ; 
 int SG_IO ; 
 int SG_SET_TIMEOUT ; 
 int linux_ioctl_sg_io (struct thread*,struct linux_ioctl_args*) ; 
 int sys_ioctl (struct thread*,struct ioctl_args*) ; 

__attribute__((used)) static int
linux_ioctl_sg(struct thread *td, struct linux_ioctl_args *args)
{

	switch (args->cmd) {
	case LINUX_SG_GET_VERSION_NUM:
		args->cmd = SG_GET_VERSION_NUM;
		break;
	case LINUX_SG_SET_TIMEOUT:
		args->cmd = SG_SET_TIMEOUT;
		break;
	case LINUX_SG_GET_TIMEOUT:
		args->cmd = SG_GET_TIMEOUT;
		break;
	case LINUX_SG_IO:
		args->cmd = SG_IO;
#ifdef COMPAT_LINUX32
		return (linux_ioctl_sg_io(td, args));
#endif
		break;
	case LINUX_SG_GET_RESERVED_SIZE:
		args->cmd = SG_GET_RESERVED_SIZE;
		break;
	case LINUX_SG_GET_SCSI_ID:
		args->cmd = SG_GET_SCSI_ID;
		break;
	case LINUX_SG_GET_SG_TABLESIZE:
		args->cmd = SG_GET_SG_TABLESIZE;
		break;
	default:
		return (ENODEV);
	}
	return (sys_ioctl(td, (struct ioctl_args *)args));
}