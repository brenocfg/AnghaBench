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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;
typedef  enum ctxt_type { ____Placeholder_ctxt_type } ctxt_type ;

/* Variables and functions */
 int /*<<< orphan*/  A_SGE_CTXT_CMD ; 
 int A_SGE_CTXT_DATA0 ; 
 int A_SGE_CTXT_DATA5 ; 
 int /*<<< orphan*/  F_BUSY ; 
 int V_CTXTQID (unsigned int) ; 
 int V_CTXTTYPE (int) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int) ; 
 int t4_wait_op_done (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

int t4_sge_ctxt_rd_bd(struct adapter *adap, unsigned int cid, enum ctxt_type ctype,
		      u32 *data)
{
	int i, ret;

	t4_write_reg(adap, A_SGE_CTXT_CMD, V_CTXTQID(cid) | V_CTXTTYPE(ctype));
	ret = t4_wait_op_done(adap, A_SGE_CTXT_CMD, F_BUSY, 0, 3, 1);
	if (!ret)
		for (i = A_SGE_CTXT_DATA0; i <= A_SGE_CTXT_DATA5; i += 4)
			*data++ = t4_read_reg(adap, i);
	return ret;
}