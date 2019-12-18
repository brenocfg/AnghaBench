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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct nae_port_config {int max_stg2_offset; int stg1_2_credit; int max_eh_offset; int stg2_eh_credit; int max_frout_offset; int stg2_frout_credit; int max_ms_offset; int stg2_ms_credit; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAE_EH_FREECRDT_CMD ; 
 int /*<<< orphan*/  NAE_STG1_STG2CRDT_CMD ; 
 int /*<<< orphan*/  NAE_STG2_EHCRDT_CMD ; 
 int /*<<< orphan*/  NAE_STG2_STRCRDT_CMD ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
config_egress_fifo_credits(uint64_t nae_base, int hwport, int start_ctxt,
    int num_ctxts, int max_ctxts, struct nae_port_config *cfg)
{
	uint32_t data, credit, max_credit;
	int i, limit;

	limit = start_ctxt + num_ctxts;
	/* Stage1 -> Stage2 */
	max_credit = cfg[hwport].max_stg2_offset + 1;
	for (i = start_ctxt; i < limit; i++) {
		credit = cfg[hwport].stg1_2_credit / max_ctxts;
		if (credit > max_credit)
		    credit = max_credit;
		data = credit << 16	|
		    i << 4		|
		    1;
		nlm_write_nae_reg(nae_base, NAE_STG1_STG2CRDT_CMD, data);
	}

	/* Stage2 -> EH */
	max_credit = cfg[hwport].max_eh_offset + 1;
	for (i = start_ctxt; i < limit; i++) {
		credit = cfg[hwport].stg2_eh_credit / max_ctxts;
		if (credit > max_credit)
			credit = max_credit;
		data = credit << 16	|
		    i << 4		|
		    1;
		nlm_write_nae_reg(nae_base, NAE_STG2_EHCRDT_CMD, data);
	}

	/* Stage2 -> Frout */
	max_credit = cfg[hwport].max_frout_offset + 1;
	for (i = start_ctxt; i < limit; i++) {
		credit = cfg[hwport].stg2_frout_credit / max_ctxts;
		if (credit > max_credit)
			credit = max_credit;
		data = credit << 16	|
		    i << 4		|
		    1;
		nlm_write_nae_reg(nae_base, NAE_EH_FREECRDT_CMD, data);
	}

	/* Stage2 -> MS */
	max_credit = cfg[hwport].max_ms_offset + 1;
	for (i = start_ctxt; i < limit; i++) {
		credit = cfg[hwport].stg2_ms_credit / max_ctxts;
		if (credit > max_credit)
			credit = max_credit;
		data = credit << 16	|
		    i << 4		|
		    1;
		nlm_write_nae_reg(nae_base, NAE_STG2_STRCRDT_CMD, data);
	}
}