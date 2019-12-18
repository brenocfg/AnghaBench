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
typedef  void* uint8_t ;
typedef  scalar_t__ uint32_t ;
struct scsi_read_defect_data_12 {int /*<<< orphan*/  address_descriptor_index; int /*<<< orphan*/  alloc_length; void* format; int /*<<< orphan*/  opcode; } ;
struct scsi_read_defect_data_10 {int /*<<< orphan*/  address_descriptor_index; int /*<<< orphan*/  alloc_length; void* format; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  READ_DEFECT_DATA_10 ; 
 int /*<<< orphan*/  READ_DEFECT_DATA_12 ; 
 scalar_t__ SRDD10_MAX_LENGTH ; 
 int /*<<< orphan*/  bzero (struct scsi_read_defect_data_12*,void*) ; 
 int /*<<< orphan*/  cam_fill_csio (struct ccb_scsiio*,scalar_t__,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,void*,void**,scalar_t__,void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  scsi_ulto2b (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (scalar_t__,int /*<<< orphan*/ ) ; 

void
scsi_read_defects(struct ccb_scsiio *csio, uint32_t retries,
		  void (*cbfcnp)(struct cam_periph *, union ccb *),
		  uint8_t tag_action, uint8_t list_format,
		  uint32_t addr_desc_index, uint8_t *data_ptr,
		  uint32_t dxfer_len, int minimum_cmd_size,
		  uint8_t sense_len, uint32_t timeout)
{
	uint8_t cdb_len;

	/*
	 * These conditions allow using the 10 byte command.  Otherwise we
	 * need to use the 12 byte command.
	 */
	if ((minimum_cmd_size <= 10)
	 && (addr_desc_index == 0)
	 && (dxfer_len <= SRDD10_MAX_LENGTH)) {
		struct scsi_read_defect_data_10 *cdb10;

		cdb10 = (struct scsi_read_defect_data_10 *)
			&csio->cdb_io.cdb_bytes;

		cdb_len = sizeof(*cdb10);
		bzero(cdb10, cdb_len);
                cdb10->opcode = READ_DEFECT_DATA_10;
                cdb10->format = list_format;
                scsi_ulto2b(dxfer_len, cdb10->alloc_length);
	} else {
		struct scsi_read_defect_data_12 *cdb12;

		cdb12 = (struct scsi_read_defect_data_12 *)
			&csio->cdb_io.cdb_bytes;

		cdb_len = sizeof(*cdb12);
		bzero(cdb12, cdb_len);
                cdb12->opcode = READ_DEFECT_DATA_12;
                cdb12->format = list_format;
                scsi_ulto4b(dxfer_len, cdb12->alloc_length);
		scsi_ulto4b(addr_desc_index, cdb12->address_descriptor_index);
	}

	cam_fill_csio(csio,
		      retries,
		      cbfcnp,
		      /*flags*/ CAM_DIR_IN,
		      tag_action,
		      data_ptr,
		      dxfer_len,
		      sense_len,
		      cdb_len,
		      timeout);
}