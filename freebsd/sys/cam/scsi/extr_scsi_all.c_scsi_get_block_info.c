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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  u_int ;
struct scsi_sense_data_fixed {int flags; } ;
struct scsi_sense_data_desc {int dummy; } ;
struct scsi_sense_data {int dummy; } ;
struct scsi_sense_block {int byte3; } ;
struct scsi_inquiry_data {int dummy; } ;
typedef  int scsi_sense_data_type ;

/* Variables and functions */
 int SID_TYPE (struct scsi_inquiry_data*) ; 
 int /*<<< orphan*/  SSD_DESC_BLOCK ; 
 int /*<<< orphan*/  SSD_FIXED_IS_PRESENT (struct scsi_sense_data_fixed*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SSD_ILI ; 
#define  SSD_TYPE_DESC 132 
#define  SSD_TYPE_FIXED 131 
#define  T_DIRECT 130 
#define  T_RBC 129 
#define  T_ZBC_HM 128 
 int /*<<< orphan*/  flags ; 
 scalar_t__ scsi_find_desc (struct scsi_sense_data_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scsi_sense_type (struct scsi_sense_data*) ; 

int
scsi_get_block_info(struct scsi_sense_data *sense_data, u_int sense_len,
		    struct scsi_inquiry_data *inq_data, uint8_t *block_bits)
{
	scsi_sense_data_type sense_type;

	if (inq_data != NULL) {
		switch (SID_TYPE(inq_data)) {
		case T_DIRECT:
		case T_RBC:
		case T_ZBC_HM:
			break;
		default:
			goto bailout;
			break;
		}
	}

	sense_type = scsi_sense_type(sense_data);

	switch (sense_type) {
	case SSD_TYPE_DESC: {
		struct scsi_sense_data_desc *sense;
		struct scsi_sense_block *block;

		sense = (struct scsi_sense_data_desc *)sense_data;

		block = (struct scsi_sense_block *)scsi_find_desc(sense,
		    sense_len, SSD_DESC_BLOCK);
		if (block == NULL)
			goto bailout;

		*block_bits = block->byte3;
		break;
	}
	case SSD_TYPE_FIXED: {
		struct scsi_sense_data_fixed *sense;

		sense = (struct scsi_sense_data_fixed *)sense_data;

		if (SSD_FIXED_IS_PRESENT(sense, sense_len, flags) == 0)
			goto bailout;

		*block_bits = sense->flags & SSD_ILI;
		break;
	}
	default:
		goto bailout;
		break;
	}
	return (0);
bailout:
	return (1);
}