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
typedef  int u32 ;
struct cper_mem_err_compact {int validation_bits; int /*<<< orphan*/  target_id; int /*<<< orphan*/  responder_id; int /*<<< orphan*/  requestor_id; int /*<<< orphan*/  bit_pos; int /*<<< orphan*/  column; int /*<<< orphan*/  row; int /*<<< orphan*/  device; int /*<<< orphan*/  bank; int /*<<< orphan*/  rank; int /*<<< orphan*/  module; int /*<<< orphan*/  card; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int CPER_MEM_VALID_BANK ; 
 int CPER_MEM_VALID_BIT_POSITION ; 
 int CPER_MEM_VALID_CARD ; 
 int CPER_MEM_VALID_COLUMN ; 
 int CPER_MEM_VALID_DEVICE ; 
 int CPER_MEM_VALID_MODULE ; 
 int CPER_MEM_VALID_NODE ; 
 int CPER_MEM_VALID_RANK_NUMBER ; 
 int CPER_MEM_VALID_REQUESTOR_ID ; 
 int CPER_MEM_VALID_RESPONDER_ID ; 
 int CPER_MEM_VALID_ROW ; 
 int CPER_MEM_VALID_TARGET_ID ; 
 int CPER_REC_LEN ; 
 scalar_t__ scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cper_mem_err_location(struct cper_mem_err_compact *mem, char *msg)
{
	u32 len, n;

	if (!msg)
		return 0;

	n = 0;
	len = CPER_REC_LEN - 1;
	if (mem->validation_bits & CPER_MEM_VALID_NODE)
		n += scnprintf(msg + n, len - n, "node: %d ", mem->node);
	if (mem->validation_bits & CPER_MEM_VALID_CARD)
		n += scnprintf(msg + n, len - n, "card: %d ", mem->card);
	if (mem->validation_bits & CPER_MEM_VALID_MODULE)
		n += scnprintf(msg + n, len - n, "module: %d ", mem->module);
	if (mem->validation_bits & CPER_MEM_VALID_RANK_NUMBER)
		n += scnprintf(msg + n, len - n, "rank: %d ", mem->rank);
	if (mem->validation_bits & CPER_MEM_VALID_BANK)
		n += scnprintf(msg + n, len - n, "bank: %d ", mem->bank);
	if (mem->validation_bits & CPER_MEM_VALID_DEVICE)
		n += scnprintf(msg + n, len - n, "device: %d ", mem->device);
	if (mem->validation_bits & CPER_MEM_VALID_ROW)
		n += scnprintf(msg + n, len - n, "row: %d ", mem->row);
	if (mem->validation_bits & CPER_MEM_VALID_COLUMN)
		n += scnprintf(msg + n, len - n, "column: %d ", mem->column);
	if (mem->validation_bits & CPER_MEM_VALID_BIT_POSITION)
		n += scnprintf(msg + n, len - n, "bit_position: %d ",
			       mem->bit_pos);
	if (mem->validation_bits & CPER_MEM_VALID_REQUESTOR_ID)
		n += scnprintf(msg + n, len - n, "requestor_id: 0x%016llx ",
			       mem->requestor_id);
	if (mem->validation_bits & CPER_MEM_VALID_RESPONDER_ID)
		n += scnprintf(msg + n, len - n, "responder_id: 0x%016llx ",
			       mem->responder_id);
	if (mem->validation_bits & CPER_MEM_VALID_TARGET_ID)
		scnprintf(msg + n, len - n, "target_id: 0x%016llx ",
			  mem->target_id);

	msg[n] = '\0';
	return n;
}