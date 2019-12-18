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
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct scsi_op_quirk_entry {int num_ops; struct op_table_entry* op_table; } ;
struct scsi_inquiry_data {int dummy; } ;
struct op_table_entry {int opcode; int opmask; char const* desc; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int SID_TYPE (struct scsi_inquiry_data*) ; 
 int T_DIRECT ; 
 int T_NODEVICE ; 
 int T_RBC ; 
 int T_ZBC_HM ; 
 int /*<<< orphan*/ * cam_quirkmatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int nitems (struct op_table_entry*) ; 
 int /*<<< orphan*/  scsi_inquiry_match ; 
 struct op_table_entry* scsi_op_codes ; 
 struct op_table_entry* scsi_op_quirk_table ; 

const char *
scsi_op_desc(u_int16_t opcode, struct scsi_inquiry_data *inq_data)
{
	caddr_t match;
	int i, j;
	u_int32_t opmask;
	u_int16_t pd_type;
	int       num_ops[2];
	struct op_table_entry *table[2];
	int num_tables;

	/*
	 * If we've got inquiry data, use it to determine what type of
	 * device we're dealing with here.  Otherwise, assume direct
	 * access.
	 */
	if (inq_data == NULL) {
		pd_type = T_DIRECT;
		match = NULL;
	} else {
		pd_type = SID_TYPE(inq_data);

		match = cam_quirkmatch((caddr_t)inq_data,
				       (caddr_t)scsi_op_quirk_table,
				       nitems(scsi_op_quirk_table),
				       sizeof(*scsi_op_quirk_table),
				       scsi_inquiry_match);
	}

	if (match != NULL) {
		table[0] = ((struct scsi_op_quirk_entry *)match)->op_table;
		num_ops[0] = ((struct scsi_op_quirk_entry *)match)->num_ops;
		table[1] = scsi_op_codes;
		num_ops[1] = nitems(scsi_op_codes);
		num_tables = 2;
	} else {
		/*	
		 * If this is true, we have a vendor specific opcode that
		 * wasn't covered in the quirk table.
		 */
		if ((opcode > 0xBF) || ((opcode > 0x5F) && (opcode < 0x80)))
			return("Vendor Specific Command");

		table[0] = scsi_op_codes;
		num_ops[0] = nitems(scsi_op_codes);
		num_tables = 1;
	}

	/* RBC is 'Simplified' Direct Access Device */
	if (pd_type == T_RBC)
		pd_type = T_DIRECT;

	/*
	 * Host managed drives are direct access for the most part.
	 */
	if (pd_type == T_ZBC_HM)
		pd_type = T_DIRECT;

	/* Map NODEVICE to Direct Access Device to handle REPORT LUNS, etc. */
	if (pd_type == T_NODEVICE)
		pd_type = T_DIRECT;

	opmask = 1 << pd_type;

	for (j = 0; j < num_tables; j++) {
		for (i = 0;i < num_ops[j] && table[j][i].opcode <= opcode; i++){
			if ((table[j][i].opcode == opcode) 
			 && ((table[j][i].opmask & opmask) != 0))
				return(table[j][i].desc);
		}
	}
	
	/*
	 * If we can't find a match for the command in the table, we just
	 * assume it's a vendor specifc command.
	 */
	return("Vendor Specific Command");

}