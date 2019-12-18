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
struct TYPE_5__ {int /*<<< orphan*/  tag_type; int /*<<< orphan*/  tag_num; int /*<<< orphan*/  task_action; } ;
struct TYPE_6__ {int /*<<< orphan*/  tag_type; int /*<<< orphan*/  tag_num; } ;
struct TYPE_4__ {int io_type; } ;
union ctl_io {TYPE_2__ taskio; TYPE_3__ scsiio; TYPE_1__ io_hdr; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  path_str ;

/* Variables and functions */
#define  CTL_IO_SCSI 130 
#define  CTL_IO_TASK 129 
#define  CTL_TASK_ABORT_TASK 128 
 int /*<<< orphan*/  ctl_scsi_command_string (TYPE_3__*,int /*<<< orphan*/ *,struct sbuf*) ; 
 int /*<<< orphan*/  ctl_scsi_path_string (union ctl_io*,char*,int) ; 
 char* ctl_scsi_task_string (TYPE_2__*) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

void
ctl_io_sbuf(union ctl_io *io, struct sbuf *sb)
{
	const char *task_desc;
	char path_str[64];

	ctl_scsi_path_string(io, path_str, sizeof(path_str));

	switch (io->io_hdr.io_type) {
	case CTL_IO_SCSI:
		sbuf_cat(sb, path_str);
		ctl_scsi_command_string(&io->scsiio, NULL, sb);
		sbuf_printf(sb, " Tag: %#x/%d\n",
			    io->scsiio.tag_num, io->scsiio.tag_type);
		break;
	case CTL_IO_TASK:
		sbuf_cat(sb, path_str);
		task_desc = ctl_scsi_task_string(&io->taskio);
		if (task_desc == NULL)
			sbuf_printf(sb, "Unknown Task Action %d (%#x)",
			    io->taskio.task_action, io->taskio.task_action);
		else
			sbuf_printf(sb, "Task Action: %s", task_desc);
		switch (io->taskio.task_action) {
		case CTL_TASK_ABORT_TASK:
			sbuf_printf(sb, " Tag: %#x/%d\n",
			    io->taskio.tag_num, io->taskio.tag_type);
			break;
		default:
			sbuf_printf(sb, "\n");
			break;
		}
		break;
	default:
		break;
	}
}