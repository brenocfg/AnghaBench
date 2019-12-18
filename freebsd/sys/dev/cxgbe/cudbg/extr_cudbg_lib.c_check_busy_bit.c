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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_CIM_HOST_ACC_CTRL ; 
 int CUDBG_CIM_BUSY_BIT ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_busy_bit(struct adapter *padap)
{
	u32 val;
	u32 busy = 1;
	int i = 0;
	int retry = 10;
	int status = 0;

	while (busy & (1 < retry)) {
		val = t4_read_reg(padap, A_CIM_HOST_ACC_CTRL);
		busy = (0 != (val & CUDBG_CIM_BUSY_BIT));
		i++;
	}

	if (busy)
		status = -1;

	return status;
}