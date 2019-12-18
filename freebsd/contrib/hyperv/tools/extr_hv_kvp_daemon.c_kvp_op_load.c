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
struct TYPE_2__ {int kvp_op_key; void (* kvp_op_init ) () ;int (* kvp_op_exec ) (struct hv_kvp_msg*,void*) ;} ;

/* Variables and functions */
 int HV_KVP_OP_COUNT ; 
 int /*<<< orphan*/  KVP_LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 TYPE_1__* kvp_op_hdlrs ; 
 void stub1 () ; 

__attribute__((used)) static int
kvp_op_load(int key, void (*init)(void),
	    int (*exec)(struct hv_kvp_msg *, void *))
{
	int error = 0;

	if (key < 0 || key >= HV_KVP_OP_COUNT) {
		KVP_LOG(LOG_ERR, "Operation key out of supported range\n");
		error = -1;
		goto kvp_op_load_done;
	}

	kvp_op_hdlrs[key].kvp_op_key = key;
	kvp_op_hdlrs[key].kvp_op_init = init;
	kvp_op_hdlrs[key].kvp_op_exec = exec;

	if (kvp_op_hdlrs[key].kvp_op_init != NULL)
		kvp_op_hdlrs[key].kvp_op_init();

kvp_op_load_done:
	return(error);
}