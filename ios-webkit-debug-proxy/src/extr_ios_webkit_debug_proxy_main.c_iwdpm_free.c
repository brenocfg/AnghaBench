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
struct iwdpm_struct {int dummy; } ;
typedef  TYPE_1__* iwdpm_t ;
struct TYPE_5__ {struct TYPE_5__* sim_wi_socket_addr; struct TYPE_5__* frontend; struct TYPE_5__* config; int /*<<< orphan*/  sm; int /*<<< orphan*/  iwdp; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  iwdp_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_free (int /*<<< orphan*/ ) ; 

void iwdpm_free(iwdpm_t self) {
  if (self) {
    pc_free(self->pc);
    iwdp_free(self->iwdp);
    sm_free(self->sm);
    free(self->config);
    free(self->frontend);
    free(self->sim_wi_socket_addr);
    memset(self, 0, sizeof(struct iwdpm_struct));
    free(self);
  }
}