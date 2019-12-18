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
typedef  int /*<<< orphan*/  u_int ;
struct scsi_sense_stream {int /*<<< orphan*/  length; int /*<<< orphan*/  byte3; } ;
struct scsi_sense_sks {int /*<<< orphan*/  length; int /*<<< orphan*/ * sense_key_spec; } ;
struct scsi_sense_info {int /*<<< orphan*/  length; int /*<<< orphan*/ * info; } ;
struct scsi_sense_fru {int /*<<< orphan*/  length; int /*<<< orphan*/  fru; } ;
struct scsi_sense_desc_header {int length; } ;
struct scsi_sense_data_fixed {int dummy; } ;
struct scsi_sense_data_desc {int error_code; int extra_len; int* sense_desc; int sense_key; int /*<<< orphan*/  add_sense_code_qual; int /*<<< orphan*/  add_sense_code; } ;
struct scsi_sense_data {int dummy; } ;
struct scsi_sense_command {int /*<<< orphan*/  length; int /*<<< orphan*/ * command_info; } ;

/* Variables and functions */
#define  SSD_DESC_COMMAND 132 
 int SSD_DESC_CURRENT_ERROR ; 
#define  SSD_DESC_FRU 131 
#define  SSD_DESC_INFO 130 
#define  SSD_DESC_SKS 129 
#define  SSD_DESC_STREAM 128 
 int /*<<< orphan*/  SSD_ELEM_COMMAND ; 
 int /*<<< orphan*/  SSD_ELEM_FRU ; 
 int /*<<< orphan*/  SSD_ELEM_INFO ; 
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int /*<<< orphan*/  SSD_ELEM_SKIP ; 
 int /*<<< orphan*/  SSD_ELEM_SKS ; 
 int /*<<< orphan*/  SSD_ELEM_STREAM ; 
 int SSD_ERRCODE ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int SSD_KEY ; 
 int /*<<< orphan*/  SSD_TYPE_FIXED ; 
 int /*<<< orphan*/  ctl_set_sense_data (struct scsi_sense_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ctl_sense_to_fixed(struct scsi_sense_data_desc *sense_src,
		   struct scsi_sense_data_fixed *sense_dest)
{
	int current_error;
	uint8_t *info_ptr = NULL, *cmd_ptr = NULL, *fru_ptr = NULL;
	uint8_t *sks_ptr = NULL, *stream_ptr = NULL;
	int info_size = 0, cmd_size = 0, fru_size = 0;
	int sks_size = 0, stream_size = 0;
	int pos;
	u_int sense_len;

	if ((sense_src->error_code & SSD_ERRCODE) == SSD_DESC_CURRENT_ERROR)
		current_error = 1;
	else
		current_error = 0;

	for (pos = 0; pos < (int)(sense_src->extra_len - 1);) {
		struct scsi_sense_desc_header *header;

		header = (struct scsi_sense_desc_header *)
		    &sense_src->sense_desc[pos];

		/*
		 * See if this record goes past the end of the sense data.
		 * It shouldn't, but check just in case.
		 */
		if ((pos + header->length + sizeof(*header)) >
		     sense_src->extra_len)
			break;

		switch (sense_src->sense_desc[pos]) {
		case SSD_DESC_INFO: {
			struct scsi_sense_info *info;

			info = (struct scsi_sense_info *)header;

			info_ptr = info->info;
			info_size = sizeof(info->info);

			pos += info->length +
			    sizeof(struct scsi_sense_desc_header);
			break;
		}
		case SSD_DESC_COMMAND: {
			struct scsi_sense_command *cmd;

			cmd = (struct scsi_sense_command *)header;
			cmd_ptr = cmd->command_info;
			cmd_size = sizeof(cmd->command_info);

			pos += cmd->length + 
			    sizeof(struct scsi_sense_desc_header);
			break;
		}
		case SSD_DESC_FRU: {
			struct scsi_sense_fru *fru;

			fru = (struct scsi_sense_fru *)header;
			fru_ptr = &fru->fru;
			fru_size = sizeof(fru->fru);
			pos += fru->length +
			    sizeof(struct scsi_sense_desc_header);
			break;
		}
		case SSD_DESC_SKS: {
			struct scsi_sense_sks *sks;

			sks = (struct scsi_sense_sks *)header;
			sks_ptr = sks->sense_key_spec;
			sks_size = sizeof(sks->sense_key_spec);

			pos = sks->length +
			    sizeof(struct scsi_sense_desc_header);
			break;
		}
		case SSD_DESC_STREAM: {
			struct scsi_sense_stream *stream_sense;

			stream_sense = (struct scsi_sense_stream *)header;
			stream_ptr = &stream_sense->byte3;
			stream_size = sizeof(stream_sense->byte3);
			pos = stream_sense->length +
			    sizeof(struct scsi_sense_desc_header);
			break;
		}
		default:
			/*
			 * We don't recognize this particular sense
			 * descriptor type, so just skip it.
			 */
			pos += sizeof(*header) + header->length;
			break;
		}
	}

	sense_len = SSD_FULL_SIZE;
	ctl_set_sense_data((struct scsi_sense_data *)sense_dest, &sense_len,
			   /*lun*/ NULL,
			   /*sense_format*/ SSD_TYPE_FIXED,
			   current_error,
			   /*sense_key*/ sense_src->sense_key & SSD_KEY,
			   /*asc*/ sense_src->add_sense_code,
			   /*ascq*/ sense_src->add_sense_code_qual,

			   /* Information Bytes */ 
			   (info_ptr != NULL) ? SSD_ELEM_INFO : SSD_ELEM_SKIP,
			   info_size,
			   info_ptr,

			   /* Command specific bytes */
			   (cmd_ptr != NULL) ? SSD_ELEM_COMMAND : SSD_ELEM_SKIP,
			   cmd_size,
			   cmd_ptr,

			   /* FRU */
			   (fru_ptr != NULL) ? SSD_ELEM_FRU : SSD_ELEM_SKIP,
			   fru_size,
			   fru_ptr,

			   /* Sense Key Specific */
			   (sks_ptr != NULL) ? SSD_ELEM_SKS : SSD_ELEM_SKIP,
			   sks_size,
			   sks_ptr,

			   /* Tape bits */
			   (stream_ptr != NULL) ? SSD_ELEM_STREAM : SSD_ELEM_SKIP,
			   stream_size,
			   stream_ptr,

			   SSD_ELEM_NONE);
}