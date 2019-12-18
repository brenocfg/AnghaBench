#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* iwdp_t ;
typedef  int /*<<< orphan*/  iwdp_status ;
typedef  TYPE_2__* iwdp_iwi_t ;
typedef  TYPE_3__* iwdp_iport_t ;
typedef  scalar_t__ iwdp_ipage_t ;
typedef  int /*<<< orphan*/  ht_t ;
struct TYPE_11__ {scalar_t__ s_fd; int /*<<< orphan*/ * iwi; } ;
struct TYPE_10__ {int /*<<< orphan*/  page_num_to_ipage; TYPE_3__* iport; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* remove_fd ) (TYPE_1__*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IWDP_SUCCESS ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  ht_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ ht_values (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwdp_ipage_free (scalar_t__) ; 
 int /*<<< orphan*/  iwdp_iwi_free (TYPE_2__*) ; 
 int /*<<< orphan*/  iwdp_log_disconnect (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__) ; 

iwdp_status iwdp_iwi_close(iwdp_t self, iwdp_iwi_t iwi) {
  iwdp_iport_t iport = iwi->iport;
  if (iport) {
    iwdp_log_disconnect(iport);
    // clear pointer to this iwi
    if (iport->iwi) {
      iport->iwi = NULL;
    }
  }
  // free pages
  ht_t ipage_ht = iwi->page_num_to_ipage;
  iwdp_ipage_t *ipages = (iwdp_ipage_t *)ht_values(ipage_ht);
  ht_clear(ipage_ht);
  iwdp_ipage_t *ipp;
  for (ipp = ipages; *ipp; ipp++) {
    iwdp_ipage_free((iwdp_ipage_t)*ipp);
  }
  free(ipages);
  iwdp_iwi_free(iwi);
  // close browser listener, which will close all clients
  if (iport && iport->s_fd > 0) {
    self->remove_fd(self, iport->s_fd);
  }
  return IWDP_SUCCESS;
}