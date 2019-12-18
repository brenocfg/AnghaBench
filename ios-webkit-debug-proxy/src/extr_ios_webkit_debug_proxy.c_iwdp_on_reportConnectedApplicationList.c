#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rpc_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  TYPE_2__* rpc_app_t ;
typedef  TYPE_3__* iwdp_iwi_t ;
typedef  int /*<<< orphan*/  ht_t ;
struct TYPE_12__ {int connected; int /*<<< orphan*/  iport; int /*<<< orphan*/  app_id_to_true; } ;
struct TYPE_11__ {int /*<<< orphan*/  app_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_SUCCESS ; 
 int /*<<< orphan*/  free (char**) ; 
 scalar_t__ ht_keys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwdp_add_app_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwdp_log_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwdp_remove_app_id (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  rpc_set_app (TYPE_1__*,TYPE_2__* const) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

rpc_status iwdp_on_reportConnectedApplicationList(rpc_t rpc, const rpc_app_t *apps) {
  iwdp_iwi_t iwi = (iwdp_iwi_t)rpc->state;
  ht_t app_id_ht = iwi->app_id_to_true;

  // rpc_reportSetup never comes from iOS >= 11.3
  if (!iwi->connected) {
    iwi->connected = true;
    iwdp_log_connect(iwi->iport);
  }

  if (*apps == NULL) {
    return RPC_SUCCESS;
  }

  // remove old apps
  char **old_app_ids = (char **)ht_keys(app_id_ht);
  char **oa;
  for (oa = old_app_ids; *oa; oa++) {
    const rpc_app_t *a;
    for (a = apps; *a && strcmp((*a)->app_id, *oa); a++) {
    }
    if (!*a) {
      iwdp_remove_app_id(rpc, *oa);
    }
  }
  free(old_app_ids);

  // add new apps
  const rpc_app_t *a;
  for (a = apps; *a; a++) {
    rpc_set_app(rpc, *a);
    iwdp_add_app_id(rpc, (*a)->app_id);
  }
  return RPC_SUCCESS;
}