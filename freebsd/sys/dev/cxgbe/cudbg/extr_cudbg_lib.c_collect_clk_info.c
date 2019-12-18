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
typedef  int u64 ;
struct struct_clk_info {int cclk_ps; int res; int tre; int dack_re; int dack_timer; int retransmit_min; int retransmit_max; int persist_timer_min; int persist_timer_max; int keepalive_idle_timer; int keepalive_interval; int initial_srtt; int finwait2_timer; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_buffer {scalar_t__ data; } ;
struct TYPE_3__ {int cclk; } ;
struct TYPE_4__ {TYPE_1__ vpd; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_DACK_TIMER ; 
 int /*<<< orphan*/  A_TP_FINWAIT2_TIMER ; 
 int /*<<< orphan*/  A_TP_INIT_SRTT ; 
 int /*<<< orphan*/  A_TP_KEEP_IDLE ; 
 int /*<<< orphan*/  A_TP_KEEP_INTVL ; 
 int /*<<< orphan*/  A_TP_PERS_MAX ; 
 int /*<<< orphan*/  A_TP_PERS_MIN ; 
 int /*<<< orphan*/  A_TP_RXT_MAX ; 
 int /*<<< orphan*/  A_TP_RXT_MIN ; 
 int /*<<< orphan*/  A_TP_TIMER_RESOLUTION ; 
 int CUDBG_STATUS_CCLK_NOT_DEFINED ; 
 int G_DELAYEDACKRESOLUTION (int) ; 
 int G_INITSRTT (int) ; 
 int G_TIMERRESOLUTION (int) ; 
 int compress_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int get_scratch_buff (struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  release_scratch_buff (struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int write_compression_hdr (struct cudbg_buffer*,struct cudbg_buffer*) ; 

__attribute__((used)) static int collect_clk_info(struct cudbg_init *pdbg_init,
			    struct cudbg_buffer *dbg_buff,
			    struct cudbg_error *cudbg_err)
{
	struct cudbg_buffer scratch_buff;
	struct adapter *padap = pdbg_init->adap;
	struct struct_clk_info *clk_info_buff;
	u64 tp_tick_us;
	int size;
	int rc = 0;

	if (!padap->params.vpd.cclk) {
		rc =  CUDBG_STATUS_CCLK_NOT_DEFINED;
		goto err;
	}

	size = sizeof(struct struct_clk_info);
	rc = get_scratch_buff(dbg_buff, size, &scratch_buff);
	if (rc)
		goto err;

	clk_info_buff = (struct struct_clk_info *) scratch_buff.data;

	clk_info_buff->cclk_ps = 1000000000 / padap->params.vpd.cclk;  /* in ps
	*/
	clk_info_buff->res = t4_read_reg(padap, A_TP_TIMER_RESOLUTION);
	clk_info_buff->tre = G_TIMERRESOLUTION(clk_info_buff->res);
	clk_info_buff->dack_re = G_DELAYEDACKRESOLUTION(clk_info_buff->res);
	tp_tick_us = (clk_info_buff->cclk_ps << clk_info_buff->tre) / 1000000;
	/* in us */
	clk_info_buff->dack_timer = ((clk_info_buff->cclk_ps <<
				      clk_info_buff->dack_re) / 1000000) *
				     t4_read_reg(padap, A_TP_DACK_TIMER);

	clk_info_buff->retransmit_min =
		tp_tick_us * t4_read_reg(padap, A_TP_RXT_MIN);
	clk_info_buff->retransmit_max =
		tp_tick_us * t4_read_reg(padap, A_TP_RXT_MAX);

	clk_info_buff->persist_timer_min =
		tp_tick_us * t4_read_reg(padap, A_TP_PERS_MIN);
	clk_info_buff->persist_timer_max =
		tp_tick_us * t4_read_reg(padap, A_TP_PERS_MAX);

	clk_info_buff->keepalive_idle_timer =
		tp_tick_us * t4_read_reg(padap, A_TP_KEEP_IDLE);
	clk_info_buff->keepalive_interval =
		tp_tick_us * t4_read_reg(padap, A_TP_KEEP_INTVL);

	clk_info_buff->initial_srtt =
		tp_tick_us * G_INITSRTT(t4_read_reg(padap, A_TP_INIT_SRTT));
	clk_info_buff->finwait2_timer =
		tp_tick_us * t4_read_reg(padap, A_TP_FINWAIT2_TIMER);

	rc = write_compression_hdr(&scratch_buff, dbg_buff);

	if (rc)
		goto err1;

	rc = compress_buff(&scratch_buff, dbg_buff);
err1:
	release_scratch_buff(&scratch_buff, dbg_buff);
err:
	return rc;

}