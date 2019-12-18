#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  task_status; int /*<<< orphan*/  task_action; scalar_t__ tag_num; int /*<<< orphan*/  tag_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  targ_lun; int /*<<< orphan*/  initid; } ;
struct TYPE_5__ {TYPE_1__ nexus; int /*<<< orphan*/  io_type; } ;
union ctl_io {TYPE_3__ taskio; TYPE_2__ io_hdr; } ;
typedef  scalar_t__ uint32_t ;
struct sbuf {int dummy; } ;
struct pci_vtscsi_softc {int /*<<< orphan*/  vss_ctl_fd; int /*<<< orphan*/  vss_iid; } ;
struct pci_vtscsi_ctrl_tmf {int subtype; int /*<<< orphan*/  response; scalar_t__ id; int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_IO ; 
 int /*<<< orphan*/  CTL_IO_TASK ; 
 int /*<<< orphan*/  CTL_TAG_SIMPLE ; 
 int /*<<< orphan*/  CTL_TASK_ABORT_TASK ; 
 int /*<<< orphan*/  CTL_TASK_ABORT_TASK_SET ; 
 int /*<<< orphan*/  CTL_TASK_CLEAR_ACA ; 
 int /*<<< orphan*/  CTL_TASK_CLEAR_TASK_SET ; 
 int /*<<< orphan*/  CTL_TASK_I_T_NEXUS_RESET ; 
 int /*<<< orphan*/  CTL_TASK_LUN_RESET ; 
 int /*<<< orphan*/  CTL_TASK_QUERY_TASK ; 
 int /*<<< orphan*/  CTL_TASK_QUERY_TASK_SET ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
#define  VIRTIO_SCSI_T_TMF_ABORT_TASK 135 
#define  VIRTIO_SCSI_T_TMF_ABORT_TASK_SET 134 
#define  VIRTIO_SCSI_T_TMF_CLEAR_ACA 133 
#define  VIRTIO_SCSI_T_TMF_CLEAR_TASK_SET 132 
#define  VIRTIO_SCSI_T_TMF_I_T_NEXUS_RESET 131 
#define  VIRTIO_SCSI_T_TMF_LOGICAL_UNIT_RESET 130 
#define  VIRTIO_SCSI_T_TMF_QUERY_TASK 129 
#define  VIRTIO_SCSI_T_TMF_QUERY_TASK_SET 128 
 int /*<<< orphan*/  WPRINTF (char*) ; 
 int /*<<< orphan*/  ctl_io_sbuf (union ctl_io*,struct sbuf*) ; 
 union ctl_io* ctl_scsi_alloc_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_scsi_free_io (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_scsi_zero_io (union ctl_io*) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ctl_io*) ; 
 scalar_t__ pci_vtscsi_debug ; 
 int /*<<< orphan*/  pci_vtscsi_get_lun (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_vtscsi_tmf_handle(struct pci_vtscsi_softc *sc,
    struct pci_vtscsi_ctrl_tmf *tmf)
{
	union ctl_io *io;
	int err;

	io = ctl_scsi_alloc_io(sc->vss_iid);
	ctl_scsi_zero_io(io);

	io->io_hdr.io_type = CTL_IO_TASK;
	io->io_hdr.nexus.initid = sc->vss_iid;
	io->io_hdr.nexus.targ_lun = pci_vtscsi_get_lun(tmf->lun);
	io->taskio.tag_type = CTL_TAG_SIMPLE;
	io->taskio.tag_num = (uint32_t)tmf->id;

	switch (tmf->subtype) {
	case VIRTIO_SCSI_T_TMF_ABORT_TASK:
		io->taskio.task_action = CTL_TASK_ABORT_TASK;
		break;

	case VIRTIO_SCSI_T_TMF_ABORT_TASK_SET:
		io->taskio.task_action = CTL_TASK_ABORT_TASK_SET;
		break;

	case VIRTIO_SCSI_T_TMF_CLEAR_ACA:
		io->taskio.task_action = CTL_TASK_CLEAR_ACA;
		break;

	case VIRTIO_SCSI_T_TMF_CLEAR_TASK_SET:
		io->taskio.task_action = CTL_TASK_CLEAR_TASK_SET;
		break;

	case VIRTIO_SCSI_T_TMF_I_T_NEXUS_RESET:
		io->taskio.task_action = CTL_TASK_I_T_NEXUS_RESET;
		break;

	case VIRTIO_SCSI_T_TMF_LOGICAL_UNIT_RESET:
		io->taskio.task_action = CTL_TASK_LUN_RESET;
		break;

	case VIRTIO_SCSI_T_TMF_QUERY_TASK:
		io->taskio.task_action = CTL_TASK_QUERY_TASK;
		break;

	case VIRTIO_SCSI_T_TMF_QUERY_TASK_SET:
		io->taskio.task_action = CTL_TASK_QUERY_TASK_SET;
		break;
	}

	if (pci_vtscsi_debug) {
		struct sbuf *sb = sbuf_new_auto();
		ctl_io_sbuf(io, sb);
		sbuf_finish(sb);
		DPRINTF(("pci_virtio_scsi: %s", sbuf_data(sb)));
		sbuf_delete(sb);
	}

	err = ioctl(sc->vss_ctl_fd, CTL_IO, io);
	if (err != 0)
		WPRINTF(("CTL_IO: err=%d (%s)\n", errno, strerror(errno)));

	tmf->response = io->taskio.task_status;
	ctl_scsi_free_io(io);
	return (1);
}