#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ws_t ;
typedef  TYPE_2__* rpc_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  TYPE_3__* iwdp_iws_t ;
typedef  TYPE_4__* iwdp_iwi_t ;
typedef  TYPE_5__* iwdp_iport_t ;
struct TYPE_13__ {int /*<<< orphan*/  ws_id_to_iws; } ;
struct TYPE_12__ {TYPE_5__* iport; } ;
struct TYPE_11__ {TYPE_1__* ws; } ;
struct TYPE_10__ {scalar_t__ state; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* send_frame ) (TYPE_1__*,int,int /*<<< orphan*/ ,int,char const*,size_t const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OPCODE_TEXT ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 TYPE_3__* ht_get_value (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int /*<<< orphan*/ ,int,char const*,size_t const) ; 

rpc_status iwdp_on_applicationSentData(rpc_t rpc,
    const char *app_id, const char *dest_id,
    const char *data, const size_t length) {
  iwdp_iport_t iport = ((iwdp_iwi_t)rpc->state)->iport;
  iwdp_iws_t iws = ht_get_value(iport->ws_id_to_iws, dest_id);
  if (!iws) {
    return RPC_SUCCESS;  // error but don't kill the inspector!
  }
  ws_t ws = iws->ws;
  return ws->send_frame(ws,
      true, OPCODE_TEXT, false,
      data, length);
}