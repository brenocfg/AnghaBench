#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_10__ {char* display_name; char* io_type; char* hio_type; char* cmd_tgt; char* cmd_ini; char* send_abts; char* init_task_tag; char* tgt_task_tag; char* hw_tag; char* tag; char* timeout; char* tmf_cmd; char* abort_rx_id; char* transferred; char* auto_resp; char* exp_xfer_len; char* xfer_req; char* seq_init; int /*<<< orphan*/  instance_index; TYPE_2__* hio; int /*<<< orphan*/  link; int /*<<< orphan*/  io_pending_link; int /*<<< orphan*/  io_alloc_link; int /*<<< orphan*/  ref; TYPE_1__* node; } ;
typedef  TYPE_3__ ocs_io_t ;
struct TYPE_9__ {char* reqtag; char* indicator; char* type; } ;
struct TYPE_8__ {char* display_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_SCSI_DDUMP_IO ; 
 int /*<<< orphan*/  ocs_ddump_endsection (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_ddump_section (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_ddump_value (int /*<<< orphan*/ *,char*,char*,char*) ; 
 char* ocs_io_busy (TYPE_3__*) ; 
 char* ocs_list_on_list (int /*<<< orphan*/ *) ; 
 char* ocs_ref_read_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_scsi_ini_ddump (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_scsi_tgt_ddump (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 

void
ocs_ddump_io(ocs_textbuf_t *textbuf, ocs_io_t *io)
{
	ocs_ddump_section(textbuf, "io", io->instance_index);
	ocs_ddump_value(textbuf, "display_name", "%s", io->display_name);
	ocs_ddump_value(textbuf, "node_name", "%s", io->node->display_name);

	ocs_ddump_value(textbuf, "ref_count", "%d", ocs_ref_read_count(&io->ref));
	ocs_ddump_value(textbuf, "io_type", "%d", io->io_type);
	ocs_ddump_value(textbuf, "hio_type", "%d", io->hio_type);
	ocs_ddump_value(textbuf, "cmd_tgt", "%d", io->cmd_tgt);
	ocs_ddump_value(textbuf, "cmd_ini", "%d", io->cmd_ini);
	ocs_ddump_value(textbuf, "send_abts", "%d", io->send_abts);
	ocs_ddump_value(textbuf, "init_task_tag", "0x%x", io->init_task_tag);
	ocs_ddump_value(textbuf, "tgt_task_tag", "0x%x", io->tgt_task_tag);
	ocs_ddump_value(textbuf, "hw_tag", "0x%x", io->hw_tag);
	ocs_ddump_value(textbuf, "tag", "0x%x", io->tag);
	ocs_ddump_value(textbuf, "timeout", "%d", io->timeout);
	ocs_ddump_value(textbuf, "tmf_cmd", "%d", io->tmf_cmd);
	ocs_ddump_value(textbuf, "abort_rx_id", "0x%x", io->abort_rx_id);

	ocs_ddump_value(textbuf, "busy", "%d", ocs_io_busy(io));
	ocs_ddump_value(textbuf, "transferred", "%zu", io->transferred);
	ocs_ddump_value(textbuf, "auto_resp", "%d", io->auto_resp);
	ocs_ddump_value(textbuf, "exp_xfer_len", "%d", io->exp_xfer_len);
	ocs_ddump_value(textbuf, "xfer_req", "%d", io->xfer_req);
	ocs_ddump_value(textbuf, "seq_init", "%d", io->seq_init);

	ocs_ddump_value(textbuf, "alloc_link", "%d", ocs_list_on_list(&io->io_alloc_link));
	ocs_ddump_value(textbuf, "pending_link", "%d", ocs_list_on_list(&io->io_pending_link));
	ocs_ddump_value(textbuf, "backend_link", "%d", ocs_list_on_list(&io->link));

	if (io->hio) {
		ocs_ddump_value(textbuf, "hw_tag", "%#x", io->hio->reqtag);
		ocs_ddump_value(textbuf, "hw_xri", "%#x", io->hio->indicator);
		ocs_ddump_value(textbuf, "hw_type", "%#x", io->hio->type);
	} else {
		ocs_ddump_value(textbuf, "hw_tag", "%s", "pending");
		ocs_ddump_value(textbuf, "hw_xri", "%s", "pending");
		ocs_ddump_value(textbuf, "hw_type", "%s", "pending");
	}

	ocs_scsi_ini_ddump(textbuf, OCS_SCSI_DDUMP_IO, io);
	ocs_scsi_tgt_ddump(textbuf, OCS_SCSI_DDUMP_IO, io);

	ocs_ddump_endsection(textbuf, "io", io->instance_index);
}