#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rpc_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  TYPE_2__* iwdp_iwi_t ;
typedef  int /*<<< orphan*/  ht_t ;
struct TYPE_6__ {int /*<<< orphan*/  connection_id; int /*<<< orphan*/  app_id_to_true; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* send_forwardGetListing ) (TYPE_1__*,int /*<<< orphan*/ ,char const*) ;int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_VALUE (int) ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 scalar_t__ ht_get_value (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ht_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 

rpc_status iwdp_add_app_id(rpc_t rpc, const char *app_id) {
  iwdp_iwi_t iwi = (iwdp_iwi_t)rpc->state;
  ht_t app_id_ht = iwi->app_id_to_true;
  if (ht_get_value(app_id_ht, app_id)) {
    return RPC_SUCCESS;
  }
  ht_put(app_id_ht, strdup(app_id), HT_VALUE(1));
  return rpc->send_forwardGetListing(rpc, iwi->connection_id, app_id);
}