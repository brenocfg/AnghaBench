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
struct virtio_scsi_cmd_resp {int response; } ;
typedef  int /*<<< orphan*/  cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DATA_RUN_ERR ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_SCSI_BUSY ; 
 int /*<<< orphan*/  CAM_SCSI_BUS_RESET ; 
 int /*<<< orphan*/  CAM_SCSI_IT_NEXUS_LOST ; 
 int /*<<< orphan*/  CAM_SEL_TIMEOUT ; 
#define  VIRTIO_SCSI_S_ABORTED 136 
#define  VIRTIO_SCSI_S_BAD_TARGET 135 
#define  VIRTIO_SCSI_S_BUSY 134 
#define  VIRTIO_SCSI_S_NEXUS_FAILURE 133 
#define  VIRTIO_SCSI_S_OK 132 
#define  VIRTIO_SCSI_S_OVERRUN 131 
#define  VIRTIO_SCSI_S_RESET 130 
#define  VIRTIO_SCSI_S_TARGET_FAILURE 129 
#define  VIRTIO_SCSI_S_TRANSPORT_FAILURE 128 

__attribute__((used)) static cam_status
vtscsi_scsi_cmd_cam_status(struct virtio_scsi_cmd_resp *cmd_resp)
{
	cam_status status;

	switch (cmd_resp->response) {
	case VIRTIO_SCSI_S_OK:
		status = CAM_REQ_CMP;
		break;
	case VIRTIO_SCSI_S_OVERRUN:
		status = CAM_DATA_RUN_ERR;
		break;
	case VIRTIO_SCSI_S_ABORTED:
		status = CAM_REQ_ABORTED;
		break;
	case VIRTIO_SCSI_S_BAD_TARGET:
		status = CAM_SEL_TIMEOUT;
		break;
	case VIRTIO_SCSI_S_RESET:
		status = CAM_SCSI_BUS_RESET;
		break;
	case VIRTIO_SCSI_S_BUSY:
		status = CAM_SCSI_BUSY;
		break;
	case VIRTIO_SCSI_S_TRANSPORT_FAILURE:
	case VIRTIO_SCSI_S_TARGET_FAILURE:
	case VIRTIO_SCSI_S_NEXUS_FAILURE:
		status = CAM_SCSI_IT_NEXUS_LOST;
		break;
	default: /* VIRTIO_SCSI_S_FAILURE */
		status = CAM_REQ_CMP_ERR;
		break;
	}

	return (status);
}