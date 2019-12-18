#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union ctl_io {int dummy; } ctl_io ;
struct scsi_receive_copy_operating_parameters_data {int implemented_descriptor_list_length; int /*<<< orphan*/ * list_of_implemented_descriptor_type_codes; scalar_t__ held_data_granularity; scalar_t__ inline_data_granularity; scalar_t__ data_segment_granularity; int /*<<< orphan*/  maximum_concurrent_copies; int /*<<< orphan*/  total_concurrent_copies; int /*<<< orphan*/  maximum_stream_device_transfer_size; int /*<<< orphan*/  held_data_limit; int /*<<< orphan*/  maximum_inline_data_length; int /*<<< orphan*/  maximum_segment_length; int /*<<< orphan*/  maximum_descriptor_list_length; int /*<<< orphan*/  maximum_segment_descriptor_count; int /*<<< orphan*/  maximum_cscd_descriptor_count; int /*<<< orphan*/  snlid; int /*<<< orphan*/  length; } ;
struct scsi_receive_copy_operating_parameters {int /*<<< orphan*/  length; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_1__ io_hdr; scalar_t__ kern_data_ptr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_rel_offset; scalar_t__ kern_sg_entries; scalar_t__ cdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  EC_CSCD_ID ; 
 int /*<<< orphan*/  EC_SEG_B2B ; 
 int /*<<< orphan*/  EC_SEG_REGISTER_KEY ; 
 int /*<<< orphan*/  EC_SEG_VERIFY ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RCOP_SNLID ; 
 int /*<<< orphan*/  TPC_MAX_CSCDS ; 
 int TPC_MAX_INLINE ; 
 int TPC_MAX_LIST ; 
 int /*<<< orphan*/  TPC_MAX_LISTS ; 
 int TPC_MAX_SEG ; 
 int /*<<< orphan*/  TPC_MAX_SEGS ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int scsi_4btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ ) ; 

int
ctl_receive_copy_operating_parameters(struct ctl_scsiio *ctsio)
{
	struct scsi_receive_copy_operating_parameters *cdb;
	struct scsi_receive_copy_operating_parameters_data *data;
	int retval;
	int alloc_len, total_len;

	CTL_DEBUG_PRINT(("ctl_report_supported_tmf\n"));

	cdb = (struct scsi_receive_copy_operating_parameters *)ctsio->cdb;

	retval = CTL_RETVAL_COMPLETE;

	total_len = sizeof(*data) + 4;
	alloc_len = scsi_4btoul(cdb->length);

	ctsio->kern_data_ptr = malloc(total_len, M_CTL, M_WAITOK | M_ZERO);
	ctsio->kern_sg_entries = 0;
	ctsio->kern_rel_offset = 0;
	ctsio->kern_data_len = min(total_len, alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	data = (struct scsi_receive_copy_operating_parameters_data *)ctsio->kern_data_ptr;
	scsi_ulto4b(sizeof(*data) - 4 + 4, data->length);
	data->snlid = RCOP_SNLID;
	scsi_ulto2b(TPC_MAX_CSCDS, data->maximum_cscd_descriptor_count);
	scsi_ulto2b(TPC_MAX_SEGS, data->maximum_segment_descriptor_count);
	scsi_ulto4b(TPC_MAX_LIST, data->maximum_descriptor_list_length);
	scsi_ulto4b(TPC_MAX_SEG, data->maximum_segment_length);
	scsi_ulto4b(TPC_MAX_INLINE, data->maximum_inline_data_length);
	scsi_ulto4b(0, data->held_data_limit);
	scsi_ulto4b(0, data->maximum_stream_device_transfer_size);
	scsi_ulto2b(TPC_MAX_LISTS, data->total_concurrent_copies);
	data->maximum_concurrent_copies = TPC_MAX_LISTS;
	data->data_segment_granularity = 0;
	data->inline_data_granularity = 0;
	data->held_data_granularity = 0;
	data->implemented_descriptor_list_length = 4;
	data->list_of_implemented_descriptor_type_codes[0] = EC_SEG_B2B;
	data->list_of_implemented_descriptor_type_codes[1] = EC_SEG_VERIFY;
	data->list_of_implemented_descriptor_type_codes[2] = EC_SEG_REGISTER_KEY;
	data->list_of_implemented_descriptor_type_codes[3] = EC_CSCD_ID;

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (retval);
}