#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union ctl_io {int dummy; } ctl_io ;
struct scsi_report_supported_opcodes_one {int support; int* cdb_usage; int /*<<< orphan*/  cdb_length; } ;
struct scsi_report_supported_opcodes_descr {int opcode; int /*<<< orphan*/  cdb_length; int /*<<< orphan*/  flags; int /*<<< orphan*/  service_action; } ;
struct scsi_report_supported_opcodes_all {int /*<<< orphan*/  length; struct scsi_report_supported_opcodes_descr* descr; } ;
struct scsi_report_supported_opcodes {int requested_opcode; int options; int /*<<< orphan*/  length; int /*<<< orphan*/  requested_service_action; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_1__ io_hdr; scalar_t__ kern_data_ptr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_rel_offset; scalar_t__ kern_sg_entries; scalar_t__ cdb; } ;
struct ctl_lun {TYPE_2__* be_lun; } ;
struct ctl_cmd_entry {int flags; int length; scalar_t__ execute; int /*<<< orphan*/  usage; } ;
struct TYPE_4__ {int /*<<< orphan*/  lun_type; } ;

/* Variables and functions */
 int CTL_CMD_FLAG_SA5 ; 
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
#define  RSO_OPTIONS_ALL 131 
 int RSO_OPTIONS_MASK ; 
#define  RSO_OPTIONS_OC 130 
#define  RSO_OPTIONS_OC_ASA 129 
#define  RSO_OPTIONS_OC_SA 128 
 int /*<<< orphan*/  RSO_SERVACTV ; 
 int /*<<< orphan*/  ctl_cmd_applicable (int /*<<< orphan*/ ,struct ctl_cmd_entry const*) ; 
 struct ctl_cmd_entry* ctl_cmd_table ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int,int,int,int,int) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 int scsi_4btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ ) ; 

int
ctl_report_supported_opcodes(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_report_supported_opcodes *cdb;
	const struct ctl_cmd_entry *entry, *sentry;
	struct scsi_report_supported_opcodes_all *all;
	struct scsi_report_supported_opcodes_descr *descr;
	struct scsi_report_supported_opcodes_one *one;
	int retval;
	int alloc_len, total_len;
	int opcode, service_action, i, j, num;

	CTL_DEBUG_PRINT(("ctl_report_supported_opcodes\n"));

	cdb = (struct scsi_report_supported_opcodes *)ctsio->cdb;
	retval = CTL_RETVAL_COMPLETE;

	opcode = cdb->requested_opcode;
	service_action = scsi_2btoul(cdb->requested_service_action);
	switch (cdb->options & RSO_OPTIONS_MASK) {
	case RSO_OPTIONS_ALL:
		num = 0;
		for (i = 0; i < 256; i++) {
			entry = &ctl_cmd_table[i];
			if (entry->flags & CTL_CMD_FLAG_SA5) {
				for (j = 0; j < 32; j++) {
					sentry = &((const struct ctl_cmd_entry *)
					    entry->execute)[j];
					if (ctl_cmd_applicable(
					    lun->be_lun->lun_type, sentry))
						num++;
				}
			} else {
				if (ctl_cmd_applicable(lun->be_lun->lun_type,
				    entry))
					num++;
			}
		}
		total_len = sizeof(struct scsi_report_supported_opcodes_all) +
		    num * sizeof(struct scsi_report_supported_opcodes_descr);
		break;
	case RSO_OPTIONS_OC:
		if (ctl_cmd_table[opcode].flags & CTL_CMD_FLAG_SA5) {
			ctl_set_invalid_field(/*ctsio*/ ctsio,
					      /*sks_valid*/ 1,
					      /*command*/ 1,
					      /*field*/ 2,
					      /*bit_valid*/ 1,
					      /*bit*/ 2);
			ctl_done((union ctl_io *)ctsio);
			return (CTL_RETVAL_COMPLETE);
		}
		total_len = sizeof(struct scsi_report_supported_opcodes_one) + 32;
		break;
	case RSO_OPTIONS_OC_SA:
		if ((ctl_cmd_table[opcode].flags & CTL_CMD_FLAG_SA5) == 0 ||
		    service_action >= 32) {
			ctl_set_invalid_field(/*ctsio*/ ctsio,
					      /*sks_valid*/ 1,
					      /*command*/ 1,
					      /*field*/ 2,
					      /*bit_valid*/ 1,
					      /*bit*/ 2);
			ctl_done((union ctl_io *)ctsio);
			return (CTL_RETVAL_COMPLETE);
		}
		/* FALLTHROUGH */
	case RSO_OPTIONS_OC_ASA:
		total_len = sizeof(struct scsi_report_supported_opcodes_one) + 32;
		break;
	default:
		ctl_set_invalid_field(/*ctsio*/ ctsio,
				      /*sks_valid*/ 1,
				      /*command*/ 1,
				      /*field*/ 2,
				      /*bit_valid*/ 1,
				      /*bit*/ 2);
		ctl_done((union ctl_io *)ctsio);
		return (CTL_RETVAL_COMPLETE);
	}

	alloc_len = scsi_4btoul(cdb->length);

	ctsio->kern_data_ptr = malloc(total_len, M_CTL, M_WAITOK | M_ZERO);
	ctsio->kern_sg_entries = 0;
	ctsio->kern_rel_offset = 0;
	ctsio->kern_data_len = min(total_len, alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	switch (cdb->options & RSO_OPTIONS_MASK) {
	case RSO_OPTIONS_ALL:
		all = (struct scsi_report_supported_opcodes_all *)
		    ctsio->kern_data_ptr;
		num = 0;
		for (i = 0; i < 256; i++) {
			entry = &ctl_cmd_table[i];
			if (entry->flags & CTL_CMD_FLAG_SA5) {
				for (j = 0; j < 32; j++) {
					sentry = &((const struct ctl_cmd_entry *)
					    entry->execute)[j];
					if (!ctl_cmd_applicable(
					    lun->be_lun->lun_type, sentry))
						continue;
					descr = &all->descr[num++];
					descr->opcode = i;
					scsi_ulto2b(j, descr->service_action);
					descr->flags = RSO_SERVACTV;
					scsi_ulto2b(sentry->length,
					    descr->cdb_length);
				}
			} else {
				if (!ctl_cmd_applicable(lun->be_lun->lun_type,
				    entry))
					continue;
				descr = &all->descr[num++];
				descr->opcode = i;
				scsi_ulto2b(0, descr->service_action);
				descr->flags = 0;
				scsi_ulto2b(entry->length, descr->cdb_length);
			}
		}
		scsi_ulto4b(
		    num * sizeof(struct scsi_report_supported_opcodes_descr),
		    all->length);
		break;
	case RSO_OPTIONS_OC:
		one = (struct scsi_report_supported_opcodes_one *)
		    ctsio->kern_data_ptr;
		entry = &ctl_cmd_table[opcode];
		goto fill_one;
	case RSO_OPTIONS_OC_SA:
		one = (struct scsi_report_supported_opcodes_one *)
		    ctsio->kern_data_ptr;
		entry = &ctl_cmd_table[opcode];
		entry = &((const struct ctl_cmd_entry *)
		    entry->execute)[service_action];
fill_one:
		if (ctl_cmd_applicable(lun->be_lun->lun_type, entry)) {
			one->support = 3;
			scsi_ulto2b(entry->length, one->cdb_length);
			one->cdb_usage[0] = opcode;
			memcpy(&one->cdb_usage[1], entry->usage,
			    entry->length - 1);
		} else
			one->support = 1;
		break;
	case RSO_OPTIONS_OC_ASA:
		one = (struct scsi_report_supported_opcodes_one *)
		    ctsio->kern_data_ptr;
		entry = &ctl_cmd_table[opcode];
		if (entry->flags & CTL_CMD_FLAG_SA5) {
			entry = &((const struct ctl_cmd_entry *)
			    entry->execute)[service_action];
		} else if (service_action != 0) {
			one->support = 1;
			break;
		}
		goto fill_one;
	}

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return(retval);
}