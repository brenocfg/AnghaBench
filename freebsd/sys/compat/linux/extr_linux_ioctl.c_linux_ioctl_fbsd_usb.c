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
 int ENOIOCTL ; 
#define  FBSD_LUSB_DEVICEENUMERATE 162 
#define  FBSD_LUSB_DEV_QUIRK_ADD 161 
#define  FBSD_LUSB_DEV_QUIRK_GET 160 
#define  FBSD_LUSB_DEV_QUIRK_REMOVE 159 
#define  FBSD_LUSB_DO_REQUEST 158 
#define  FBSD_LUSB_FS_CLEAR_STALL_SYNC 157 
#define  FBSD_LUSB_FS_CLOSE 156 
#define  FBSD_LUSB_FS_COMPLETE 155 
#define  FBSD_LUSB_FS_INIT 154 
#define  FBSD_LUSB_FS_OPEN 153 
#define  FBSD_LUSB_FS_OPEN_STREAM 152 
#define  FBSD_LUSB_FS_START 151 
#define  FBSD_LUSB_FS_STOP 150 
#define  FBSD_LUSB_FS_UNINIT 149 
#define  FBSD_LUSB_GET_CONFIG 148 
#define  FBSD_LUSB_GET_DEVICEINFO 147 
#define  FBSD_LUSB_GET_DEVICE_DESC 146 
#define  FBSD_LUSB_GET_DEV_PORT_PATH 145 
#define  FBSD_LUSB_GET_FULL_DESC 144 
#define  FBSD_LUSB_GET_IFACE_DRIVER 143 
#define  FBSD_LUSB_GET_PLUGTIME 142 
#define  FBSD_LUSB_GET_POWER_MODE 141 
#define  FBSD_LUSB_GET_POWER_USAGE 140 
#define  FBSD_LUSB_GET_REPORT_DESC 139 
#define  FBSD_LUSB_GET_REPORT_ID 138 
#define  FBSD_LUSB_GET_TEMPLATE 137 
#define  FBSD_LUSB_IFACE_DRIVER_ACTIVE 136 
#define  FBSD_LUSB_IFACE_DRIVER_DETACH 135 
#define  FBSD_LUSB_QUIRK_NAME_GET 134 
#define  FBSD_LUSB_READ_DIR 133 
#define  FBSD_LUSB_SET_ALTINTERFACE 132 
#define  FBSD_LUSB_SET_CONFIG 131 
#define  FBSD_LUSB_SET_IMMED 130 
#define  FBSD_LUSB_SET_POWER_MODE 129 
#define  FBSD_LUSB_SET_TEMPLATE 128 
 int USB_DEVICEENUMERATE ; 
 int USB_DEV_QUIRK_ADD ; 
 int USB_DEV_QUIRK_GET ; 
 int USB_DEV_QUIRK_REMOVE ; 
 int USB_DO_REQUEST ; 
 int USB_FS_CLEAR_STALL_SYNC ; 
 int USB_FS_CLOSE ; 
 int USB_FS_COMPLETE ; 
 int USB_FS_INIT ; 
 int USB_FS_OPEN ; 
 int USB_FS_OPEN_STREAM ; 
 int USB_FS_START ; 
 int USB_FS_STOP ; 
 int USB_FS_UNINIT ; 
 int USB_GET_CONFIG ; 
 int USB_GET_DEVICEINFO ; 
 int USB_GET_DEVICE_DESC ; 
 int USB_GET_DEV_PORT_PATH ; 
 int USB_GET_FULL_DESC ; 
 int USB_GET_IFACE_DRIVER ; 
 int USB_GET_PLUGTIME ; 
 int USB_GET_POWER_MODE ; 
 int USB_GET_POWER_USAGE ; 
 int USB_GET_REPORT_DESC ; 
 int USB_GET_REPORT_ID ; 
 int USB_GET_TEMPLATE ; 
 int USB_IFACE_DRIVER_ACTIVE ; 
 int USB_IFACE_DRIVER_DETACH ; 
 int USB_QUIRK_NAME_GET ; 
 int USB_READ_DIR ; 
 int USB_SET_ALTINTERFACE ; 
 int USB_SET_CONFIG ; 
 int USB_SET_IMMED ; 
 int USB_SET_POWER_MODE ; 
 int USB_SET_TEMPLATE ; 
 int sys_ioctl (struct thread*,struct ioctl_args*) ; 

__attribute__((used)) static int
linux_ioctl_fbsd_usb(struct thread *td, struct linux_ioctl_args *args)
{
	int error;

	error = 0;
	switch (args->cmd) {
	case FBSD_LUSB_DEVICEENUMERATE:
		args->cmd = USB_DEVICEENUMERATE;
		break;
	case FBSD_LUSB_DEV_QUIRK_ADD:
		args->cmd = USB_DEV_QUIRK_ADD;
		break;
	case FBSD_LUSB_DEV_QUIRK_GET:
		args->cmd = USB_DEV_QUIRK_GET;
		break;
	case FBSD_LUSB_DEV_QUIRK_REMOVE:
		args->cmd = USB_DEV_QUIRK_REMOVE;
		break;
	case FBSD_LUSB_DO_REQUEST:
		args->cmd = USB_DO_REQUEST;
		break;
	case FBSD_LUSB_FS_CLEAR_STALL_SYNC:
		args->cmd = USB_FS_CLEAR_STALL_SYNC;
		break;
	case FBSD_LUSB_FS_CLOSE:
		args->cmd = USB_FS_CLOSE;
		break;
	case FBSD_LUSB_FS_COMPLETE:
		args->cmd = USB_FS_COMPLETE;
		break;
	case FBSD_LUSB_FS_INIT:
		args->cmd = USB_FS_INIT;
		break;
	case FBSD_LUSB_FS_OPEN:
		args->cmd = USB_FS_OPEN;
		break;
	case FBSD_LUSB_FS_START:
		args->cmd = USB_FS_START;
		break;
	case FBSD_LUSB_FS_STOP:
		args->cmd = USB_FS_STOP;
		break;
	case FBSD_LUSB_FS_UNINIT:
		args->cmd = USB_FS_UNINIT;
		break;
	case FBSD_LUSB_GET_CONFIG:
		args->cmd = USB_GET_CONFIG;
		break;
	case FBSD_LUSB_GET_DEVICEINFO:
		args->cmd = USB_GET_DEVICEINFO;
		break;
	case FBSD_LUSB_GET_DEVICE_DESC:
		args->cmd = USB_GET_DEVICE_DESC;
		break;
	case FBSD_LUSB_GET_FULL_DESC:
		args->cmd = USB_GET_FULL_DESC;
		break;
	case FBSD_LUSB_GET_IFACE_DRIVER:
		args->cmd = USB_GET_IFACE_DRIVER;
		break;
	case FBSD_LUSB_GET_PLUGTIME:
		args->cmd = USB_GET_PLUGTIME;
		break;
	case FBSD_LUSB_GET_POWER_MODE:
		args->cmd = USB_GET_POWER_MODE;
		break;
	case FBSD_LUSB_GET_REPORT_DESC:
		args->cmd = USB_GET_REPORT_DESC;
		break;
	case FBSD_LUSB_GET_REPORT_ID:
		args->cmd = USB_GET_REPORT_ID;
		break;
	case FBSD_LUSB_GET_TEMPLATE:
		args->cmd = USB_GET_TEMPLATE;
		break;
	case FBSD_LUSB_IFACE_DRIVER_ACTIVE:
		args->cmd = USB_IFACE_DRIVER_ACTIVE;
		break;
	case FBSD_LUSB_IFACE_DRIVER_DETACH:
		args->cmd = USB_IFACE_DRIVER_DETACH;
		break;
	case FBSD_LUSB_QUIRK_NAME_GET:
		args->cmd = USB_QUIRK_NAME_GET;
		break;
	case FBSD_LUSB_READ_DIR:
		args->cmd = USB_READ_DIR;
		break;
	case FBSD_LUSB_SET_ALTINTERFACE:
		args->cmd = USB_SET_ALTINTERFACE;
		break;
	case FBSD_LUSB_SET_CONFIG:
		args->cmd = USB_SET_CONFIG;
		break;
	case FBSD_LUSB_SET_IMMED:
		args->cmd = USB_SET_IMMED;
		break;
	case FBSD_LUSB_SET_POWER_MODE:
		args->cmd = USB_SET_POWER_MODE;
		break;
	case FBSD_LUSB_SET_TEMPLATE:
		args->cmd = USB_SET_TEMPLATE;
		break;
	case FBSD_LUSB_FS_OPEN_STREAM:
		args->cmd = USB_FS_OPEN_STREAM;
		break;
	case FBSD_LUSB_GET_DEV_PORT_PATH:
		args->cmd = USB_GET_DEV_PORT_PATH;
		break;
	case FBSD_LUSB_GET_POWER_USAGE:
		args->cmd = USB_GET_POWER_USAGE;
		break;
	default:
		error = ENOIOCTL;
	}
	if (error != ENOIOCTL)
		error = sys_ioctl(td, (struct ioctl_args *)args);
	return (error);
}