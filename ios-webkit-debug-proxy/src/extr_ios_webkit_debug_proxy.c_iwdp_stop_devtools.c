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
typedef  int /*<<< orphan*/  ws_status ;
typedef  TYPE_1__* rpc_t ;
typedef  TYPE_2__* iwdp_iws_t ;
typedef  TYPE_3__* iwdp_iwi_t ;
typedef  TYPE_4__* iwdp_iport_t ;
typedef  TYPE_5__* iwdp_ipage_t ;
struct TYPE_13__ {char* sender_id; TYPE_2__* iws; int /*<<< orphan*/  page_id; int /*<<< orphan*/  app_id; int /*<<< orphan*/  connection_id; } ;
struct TYPE_12__ {TYPE_3__* iwi; int /*<<< orphan*/  ws_id_to_iws; } ;
struct TYPE_11__ {scalar_t__ connection_id; TYPE_1__* rpc; } ;
struct TYPE_10__ {scalar_t__ page_num; TYPE_5__* ipage; TYPE_4__* iport; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* send_forwardDidClose ) (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WS_ERROR ; 
 int /*<<< orphan*/  WS_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* ht_get_value (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ws_status iwdp_stop_devtools(iwdp_ipage_t ipage) {
  iwdp_iws_t iws = ipage->iws;
  if (!iws) {
    return WS_SUCCESS;
  }
  if (iws->ipage != ipage) {
    return WS_ERROR; // internal error?
  }
  char *sender_id = ipage->sender_id;
  if (!sender_id) {
    return WS_ERROR; // internal error?
  }
  iwdp_iport_t iport = iws->iport;
  iwdp_iws_t iws2 = ht_get_value(iport->ws_id_to_iws, sender_id);
  if (iws != iws2) {
    return WS_ERROR; // internal error?
  }
  iwdp_iwi_t iwi = iport->iwi;
  if (iwi && iwi->connection_id && (!ipage->connection_id ||
        !strcmp(ipage->connection_id, iwi->connection_id))) {
    // if ipage->connection_id is NULL, it's likely a normal lag between our
    // send_forwardSocketSetup and the on_applicationSentListing ack.
    rpc_t rpc = iwi->rpc;
    rpc->send_forwardDidClose(rpc,
        iwi->connection_id, ipage->app_id,
        ipage->page_id, ipage->sender_id);
  }
  // close the ws_fd?
  iws->ipage = NULL;
  iws->page_num = 0;
  ipage->iws = NULL;
  ipage->sender_id = NULL;
  free(sender_id);
  return WS_SUCCESS;
}