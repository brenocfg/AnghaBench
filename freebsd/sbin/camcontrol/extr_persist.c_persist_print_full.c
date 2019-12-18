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
typedef  int uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct scsi_per_res_in_header {int /*<<< orphan*/  generation; int /*<<< orphan*/  length; } ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
struct scsi_per_res_in_full_desc {int flags; int /*<<< orphan*/  transport_id; int /*<<< orphan*/  additional_length; int /*<<< orphan*/  rel_trgt_port_id; int /*<<< orphan*/  scopetype; TYPE_1__ res_key; } ;

/* Variables and functions */
 int MIN (int,int) ; 
 int SPRI_FULL_ALL_TG_PT ; 
 int SPRI_FULL_R_HOLDER ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  persist_print_scopetype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persist_print_transportid (int /*<<< orphan*/ ,int) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 int scsi_4btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_8btou64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static void
persist_print_full(struct scsi_per_res_in_header *hdr, uint32_t valid_len)
{
	uint32_t length, len_to_go = 0;
	struct scsi_per_res_in_full_desc *desc;
	uint8_t *cur_pos;
	int i;

	length = scsi_4btoul(hdr->length);
	length = MIN(length, valid_len);

	if (length < sizeof(*desc)) {
		if (length == 0)
			fprintf(stdout, "No reservations.\n");
		else
			warnx("unable to print reservation, only got %u "
			      "valid bytes", length);
		return;
	}

	fprintf(stdout, "PRgeneration: %#x\n", scsi_4btoul(hdr->generation));
	cur_pos = (uint8_t *)&hdr[1];
	for (len_to_go = length, i = 0,
	     desc = (struct scsi_per_res_in_full_desc *)cur_pos;
	     len_to_go >= sizeof(*desc);
	     desc = (struct scsi_per_res_in_full_desc *)cur_pos, i++) {
		uint32_t additional_length, cur_length;


		fprintf(stdout, "Reservation Key: %#jx\n",
			(uintmax_t)scsi_8btou64(desc->res_key.key));
		fprintf(stdout, "All Target Ports (ALL_TG_PT): %d\n",
			(desc->flags & SPRI_FULL_ALL_TG_PT) ? 1 : 0);
		fprintf(stdout, "Reservation Holder (R_HOLDER): %d\n",
			(desc->flags & SPRI_FULL_R_HOLDER) ? 1 : 0);
		
		if (desc->flags & SPRI_FULL_R_HOLDER)
			persist_print_scopetype(desc->scopetype);

		if ((desc->flags & SPRI_FULL_ALL_TG_PT) == 0)
			fprintf(stdout, "Relative Target Port ID: %#x\n",
				scsi_2btoul(desc->rel_trgt_port_id));

		additional_length = scsi_4btoul(desc->additional_length);

		persist_print_transportid(desc->transport_id,
					  additional_length);

		cur_length = sizeof(*desc) + additional_length;
		len_to_go -= cur_length;
		cur_pos += cur_length;
	}
}