#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rpc_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  TYPE_2__* iwdp_iwi_t ;
struct TYPE_5__ {int connected; int /*<<< orphan*/  iport; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_SUCCESS ; 
 int /*<<< orphan*/  iwdp_log_connect (int /*<<< orphan*/ ) ; 

rpc_status iwdp_on_reportSetup(rpc_t rpc) {
  iwdp_iwi_t iwi = (iwdp_iwi_t)rpc->state;
  iwi->connected = true;
  iwdp_log_connect(iwi->iport);
  return RPC_SUCCESS;
}