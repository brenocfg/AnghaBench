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
struct adapter {int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_CMD_MAX_TIMEOUT ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_MCINIT ; 
 int V_FW_PARAMS_MNEM (int /*<<< orphan*/ ) ; 
 int V_FW_PARAMS_PARAM_X (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_t5 (struct adapter*) ; 
 int t4_set_params_timeout (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ ) ; 

int t5_fw_init_extern_mem(struct adapter *adap)
{
	u32 params[1], val[1];
	int ret;

	if (!is_t5(adap))
		return 0;

	val[0] = 0xff; /* Initialize all MCs */
	params[0] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_DEV) |
			V_FW_PARAMS_PARAM_X(FW_PARAMS_PARAM_DEV_MCINIT));
	ret = t4_set_params_timeout(adap, adap->mbox, adap->pf, 0, 1, params, val,
			FW_CMD_MAX_TIMEOUT);

	return ret;
}