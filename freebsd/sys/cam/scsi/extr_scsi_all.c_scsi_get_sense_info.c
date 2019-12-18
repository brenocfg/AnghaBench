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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
struct scsi_sense_info {int byte2; int /*<<< orphan*/  info; } ;
struct scsi_sense_fru {int /*<<< orphan*/  fru; } ;
struct scsi_sense_data_fixed {int error_code; int /*<<< orphan*/  fru; int /*<<< orphan*/  cmd_spec_info; int /*<<< orphan*/  info; } ;
struct scsi_sense_data_desc {int dummy; } ;
struct scsi_sense_data {int dummy; } ;
struct scsi_sense_command {int /*<<< orphan*/  command_info; } ;
typedef  int scsi_sense_data_type ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  SSD_DESC_COMMAND 132 
#define  SSD_DESC_FRU 131 
#define  SSD_DESC_INFO 130 
 int SSD_ERRCODE_VALID ; 
 int /*<<< orphan*/  SSD_FIXED_IS_FILLED (struct scsi_sense_data_fixed*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSD_FIXED_IS_PRESENT (struct scsi_sense_data_fixed*,scalar_t__,int /*<<< orphan*/ *) ; 
 int SSD_INFO_VALID ; 
#define  SSD_TYPE_DESC 129 
#define  SSD_TYPE_FIXED 128 
 int /*<<< orphan*/ * cmd_spec_info ; 
 int /*<<< orphan*/ * fru ; 
 int /*<<< orphan*/  scsi_4btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_8btou64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * scsi_find_desc (struct scsi_sense_data_desc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int scsi_sense_type (struct scsi_sense_data*) ; 

int
scsi_get_sense_info(struct scsi_sense_data *sense_data, u_int sense_len,
		    uint8_t info_type, uint64_t *info, int64_t *signed_info)
{
	scsi_sense_data_type sense_type;

	if (sense_len == 0)
		goto bailout;

	sense_type = scsi_sense_type(sense_data);

	switch (sense_type) {
	case SSD_TYPE_DESC: {
		struct scsi_sense_data_desc *sense;
		uint8_t *desc;

		sense = (struct scsi_sense_data_desc *)sense_data;

		desc = scsi_find_desc(sense, sense_len, info_type);
		if (desc == NULL)
			goto bailout;

		switch (info_type) {
		case SSD_DESC_INFO: {
			struct scsi_sense_info *info_desc;

			info_desc = (struct scsi_sense_info *)desc;

			if ((info_desc->byte2 & SSD_INFO_VALID) == 0)
				goto bailout;

			*info = scsi_8btou64(info_desc->info);
			if (signed_info != NULL)
				*signed_info = *info;
			break;
		}
		case SSD_DESC_COMMAND: {
			struct scsi_sense_command *cmd_desc;

			cmd_desc = (struct scsi_sense_command *)desc;

			*info = scsi_8btou64(cmd_desc->command_info);
			if (signed_info != NULL)
				*signed_info = *info;
			break;
		}
		case SSD_DESC_FRU: {
			struct scsi_sense_fru *fru_desc;

			fru_desc = (struct scsi_sense_fru *)desc;

			if (fru_desc->fru == 0)
				goto bailout;

			*info = fru_desc->fru;
			if (signed_info != NULL)
				*signed_info = (int8_t)fru_desc->fru;
			break;
		}
		default:
			goto bailout;
			break;
		}
		break;
	}
	case SSD_TYPE_FIXED: {
		struct scsi_sense_data_fixed *sense;

		sense = (struct scsi_sense_data_fixed *)sense_data;

		switch (info_type) {
		case SSD_DESC_INFO: {
			uint32_t info_val;

			if ((sense->error_code & SSD_ERRCODE_VALID) == 0)
				goto bailout;

			if (SSD_FIXED_IS_PRESENT(sense, sense_len, info) == 0)
				goto bailout;

			info_val = scsi_4btoul(sense->info);

			*info = info_val;
			if (signed_info != NULL)
				*signed_info = (int32_t)info_val;
			break;
		}
		case SSD_DESC_COMMAND: {
			uint32_t cmd_val;

			if ((SSD_FIXED_IS_PRESENT(sense, sense_len,
			     cmd_spec_info) == 0)
			 || (SSD_FIXED_IS_FILLED(sense, cmd_spec_info) == 0)) 
				goto bailout;

			cmd_val = scsi_4btoul(sense->cmd_spec_info);
			if (cmd_val == 0)
				goto bailout;

			*info = cmd_val;
			if (signed_info != NULL)
				*signed_info = (int32_t)cmd_val;
			break;
		}
		case SSD_DESC_FRU:
			if ((SSD_FIXED_IS_PRESENT(sense, sense_len, fru) == 0)
			 || (SSD_FIXED_IS_FILLED(sense, fru) == 0))
				goto bailout;

			if (sense->fru == 0)
				goto bailout;

			*info = sense->fru;
			if (signed_info != NULL)
				*signed_info = (int8_t)sense->fru;
			break;
		default:
			goto bailout;
			break;
		}
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