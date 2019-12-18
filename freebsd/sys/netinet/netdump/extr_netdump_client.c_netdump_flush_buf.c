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
struct debugnet_proto_aux {int /*<<< orphan*/  dp_offset_start; } ;
struct TYPE_2__ {scalar_t__ nd_buf_len; int /*<<< orphan*/  nd_pcb; int /*<<< orphan*/  nd_tx_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGNET_DATA ; 
 int debugnet_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct debugnet_proto_aux*) ; 
 int /*<<< orphan*/  nd_buf ; 
 TYPE_1__ nd_conf ; 

__attribute__((used)) static int
netdump_flush_buf(void)
{
	int error;

	error = 0;
	if (nd_conf.nd_buf_len != 0) {
		struct debugnet_proto_aux auxdata = {
			.dp_offset_start = nd_conf.nd_tx_off,
		};
		error = debugnet_send(nd_conf.nd_pcb, DEBUGNET_DATA, nd_buf,
		    nd_conf.nd_buf_len, &auxdata);
		if (error == 0)
			nd_conf.nd_buf_len = 0;
	}
	return (error);
}