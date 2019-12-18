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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_CIM_HOST_ACC_CTRL ; 
 int /*<<< orphan*/  A_CIM_HOST_ACC_DATA ; 
 int EBUSY ; 
 int F_HOSTBUSY ; 
 unsigned int F_HOSTWRITE ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_wait_op_done (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,unsigned int) ; 

int t4_cim_write(struct adapter *adap, unsigned int addr, unsigned int n,
		 const unsigned int *valp)
{
	int ret = 0;

	if (t4_read_reg(adap, A_CIM_HOST_ACC_CTRL) & F_HOSTBUSY)
		return -EBUSY;

	for ( ; !ret && n--; addr += 4) {
		t4_write_reg(adap, A_CIM_HOST_ACC_DATA, *valp++);
		t4_write_reg(adap, A_CIM_HOST_ACC_CTRL, addr | F_HOSTWRITE);
		ret = t4_wait_op_done(adap, A_CIM_HOST_ACC_CTRL, F_HOSTBUSY,
				      0, 5, 2);
	}
	return ret;
}