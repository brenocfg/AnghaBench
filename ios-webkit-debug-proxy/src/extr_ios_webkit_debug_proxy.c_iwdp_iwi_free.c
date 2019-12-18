#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iwdp_iwi_struct {int dummy; } ;
typedef  TYPE_1__* iwdp_iwi_t ;
struct TYPE_5__ {int /*<<< orphan*/  page_num_to_ipage; int /*<<< orphan*/  app_id_to_true; struct TYPE_5__* connection_id; int /*<<< orphan*/  app; int /*<<< orphan*/  rpc; int /*<<< orphan*/  wi; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ht_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_free_app (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wi_free (int /*<<< orphan*/ ) ; 

void iwdp_iwi_free(iwdp_iwi_t iwi) {
  if (iwi) {
    wi_free(iwi->wi);
    rpc_free(iwi->rpc);
    rpc_free_app(iwi->app);
    // TODO free ht_values?
    free(iwi->connection_id);
    ht_free(iwi->app_id_to_true);
    ht_free(iwi->page_num_to_ipage);
    memset(iwi, 0, sizeof(struct iwdp_iwi_struct));
    free(iwi);
  }
}