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
typedef  int u32 ;
struct struct_hw_sched {int /*<<< orphan*/ * ipg; int /*<<< orphan*/ * kbps; int /*<<< orphan*/  pace_tab; int /*<<< orphan*/  mode; int /*<<< orphan*/  map; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  cclk; } ;
struct TYPE_4__ {TYPE_1__ vpd; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_MOD_CONFIG ; 
 int /*<<< orphan*/  A_TP_TX_MOD_QUEUE_REQ_MAP ; 
 int CUDBG_STATUS_CCLK_NOT_DEFINED ; 
 int /*<<< orphan*/  G_TIMERMODE (int /*<<< orphan*/ ) ; 
 int NTX_SCHED ; 
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int get_scratch_buff (struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  t4_get_tx_sched (struct adapter*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  t4_read_pace_tbl (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_hw_sched(struct cudbg_init *pdbg_init,
			    struct cudbg_buffer *dbg_buff,
			    struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer scratch_buff;
	struct struct_hw_sched *hw_sched_buff;
	u32 size;
	int i, rc = 0;

	if (!padap->params.vpd.cclk) {
		rc =  CUDBG_STATUS_CCLK_NOT_DEFINED;
		goto err;
	}

	size = sizeof(struct struct_hw_sched);
	rc = get_scratch_buff(dbg_buff, size, &scratch_buff);
	if (rc)
		goto err;

	hw_sched_buff = (struct struct_hw_sched *) scratch_buff.data;

	hw_sched_buff->map = t4_read_reg(padap, A_TP_TX_MOD_QUEUE_REQ_MAP);
	hw_sched_buff->mode = G_TIMERMODE(t4_read_reg(padap, A_TP_MOD_CONFIG));
	t4_read_pace_tbl(padap, hw_sched_buff->pace_tab);

	for (i = 0; i < NTX_SCHED; ++i) {
		t4_get_tx_sched(padap, i, &hw_sched_buff->kbps[i],
		    &hw_sched_buff->ipg[i], 1);
	}

	rc = write_compression_hdr(&scratch_buff, dbg_buff);
	if (rc)
		goto err1;

	rc = compress_buff(&scratch_buff, dbg_buff);
err1:
	release_scratch_buff(&scratch_buff, dbg_buff);
err:
	return rc;
}