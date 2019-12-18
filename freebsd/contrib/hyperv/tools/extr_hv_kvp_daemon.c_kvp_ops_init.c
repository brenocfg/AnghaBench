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
struct TYPE_2__ {int kvp_op_key; int /*<<< orphan*/ * kvp_op_exec; int /*<<< orphan*/ * kvp_op_init; } ;

/* Variables and functions */
 int HV_KVP_OP_COUNT ; 
 int /*<<< orphan*/  HV_KVP_OP_DELETE ; 
 int /*<<< orphan*/  HV_KVP_OP_ENUMERATE ; 
 int /*<<< orphan*/  HV_KVP_OP_GET ; 
 int /*<<< orphan*/  HV_KVP_OP_GET_IP_INFO ; 
 int /*<<< orphan*/  HV_KVP_OP_SET ; 
 int /*<<< orphan*/  HV_KVP_OP_SET_IP_INFO ; 
 int /*<<< orphan*/ * kvp_get_os_info ; 
 int /*<<< orphan*/  kvp_op_enumerate ; 
 int /*<<< orphan*/  kvp_op_getipinfo ; 
 TYPE_1__* kvp_op_hdlrs ; 
 int kvp_op_load (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvp_op_setgetdel ; 
 int /*<<< orphan*/  kvp_op_setipinfo ; 

__attribute__((used)) static int
kvp_ops_init(void)
{
	int i;

	/* Set the initial values. */
	for (i = 0; i < HV_KVP_OP_COUNT; i++) {
		kvp_op_hdlrs[i].kvp_op_key = -1;
		kvp_op_hdlrs[i].kvp_op_init = NULL;
		kvp_op_hdlrs[i].kvp_op_exec = NULL;
	}

	return(kvp_op_load(HV_KVP_OP_GET, NULL, kvp_op_setgetdel) |
	    kvp_op_load(HV_KVP_OP_SET, NULL, kvp_op_setgetdel) |
	    kvp_op_load(HV_KVP_OP_DELETE, NULL, kvp_op_setgetdel) |
	    kvp_op_load(HV_KVP_OP_ENUMERATE, kvp_get_os_info,
	        kvp_op_enumerate) |
	    kvp_op_load(HV_KVP_OP_GET_IP_INFO, NULL, kvp_op_getipinfo) |
	    kvp_op_load(HV_KVP_OP_SET_IP_INFO, NULL, kvp_op_setipinfo));
}