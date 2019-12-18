#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  els_req_cnt; } ;
typedef  TYPE_1__ ocs_node_t ;
struct TYPE_7__ {int /*<<< orphan*/  wire_len; TYPE_1__* node; } ;
typedef  TYPE_2__ ocs_io_t ;
typedef  int /*<<< orphan*/  ocs_hw_srrs_cb_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_els_make_active (TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_scsi_io_dispatch (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_els_send(ocs_io_t *els, uint32_t reqlen, uint32_t timeout_sec, ocs_hw_srrs_cb_t cb)
{
	ocs_node_t *node = els->node;

	/* update ELS request counter */
	node->els_req_cnt++;

	/* move ELS from pending list to active list */
	ocs_els_make_active(els);

	els->wire_len = reqlen;
	return ocs_scsi_io_dispatch(els, cb);
}