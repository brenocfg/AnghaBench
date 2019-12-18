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
typedef  int cam_status ;

/* Variables and functions */
#define  CAM_BUSY 142 
#define  CAM_CMD_TIMEOUT 141 
#define  CAM_DEV_NOT_THERE 140 
#define  CAM_FUNC_NOTAVAIL 139 
#define  CAM_LUN_ALRDY_ENA 138 
#define  CAM_PATH_INVALID 137 
#define  CAM_PROVIDE_FAIL 136 
#define  CAM_REQUEUE_REQ 135 
#define  CAM_REQ_ABORTED 134 
#define  CAM_REQ_CMP 133 
#define  CAM_REQ_CMP_ERR 132 
#define  CAM_REQ_INPROG 131 
#define  CAM_REQ_INVALID 130 
#define  CAM_RESRC_UNAVAIL 129 
 int CAM_STATUS_MASK ; 
#define  CAM_UA_ABORT 128 
 int EADDRINUSE ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ECANCELED ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int ENOTTY ; 
 int ENXIO ; 
 int ETIMEDOUT ; 

__attribute__((used)) static int
targcamstatus(cam_status status)
{
	switch (status & CAM_STATUS_MASK) {
	case CAM_REQ_CMP:	/* CCB request completed without error */
		return (0);
	case CAM_REQ_INPROG:	/* CCB request is in progress */
		return (EINPROGRESS);
	case CAM_REQ_CMP_ERR:	/* CCB request completed with an error */
		return (EIO);
	case CAM_PROVIDE_FAIL:	/* Unable to provide requested capability */
		return (ENOTTY);
	case CAM_FUNC_NOTAVAIL:	/* The requested function is not available */
		return (ENOTSUP);
	case CAM_LUN_ALRDY_ENA:	/* LUN is already enabled for target mode */
		return (EADDRINUSE);
	case CAM_PATH_INVALID:	/* Supplied Path ID is invalid */
	case CAM_DEV_NOT_THERE:	/* SCSI Device Not Installed/there */
		return (ENOENT);
	case CAM_REQ_ABORTED:	/* CCB request aborted by the host */
		return (ECANCELED);
	case CAM_CMD_TIMEOUT:	/* Command timeout */
		return (ETIMEDOUT);
	case CAM_REQUEUE_REQ:	/* Requeue to preserve transaction ordering */
		return (EAGAIN);
	case CAM_REQ_INVALID:	/* CCB request was invalid */
		return (EINVAL);
	case CAM_RESRC_UNAVAIL:	/* Resource Unavailable */
		return (ENOMEM);
	case CAM_BUSY:		/* CAM subsystem is busy */
	case CAM_UA_ABORT:	/* Unable to abort CCB request */
		return (EBUSY);
	default:
		return (ENXIO);
	}
}