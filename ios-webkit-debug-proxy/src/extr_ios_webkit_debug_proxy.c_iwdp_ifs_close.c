#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* iwdp_t ;
typedef  int /*<<< orphan*/  iwdp_status ;
typedef  TYPE_2__* iwdp_iws_t ;
typedef  TYPE_3__* iwdp_ifs_t ;
struct TYPE_10__ {TYPE_2__* iws; } ;
struct TYPE_9__ {scalar_t__ ws_fd; TYPE_3__* ifs; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* remove_fd ) (TYPE_1__*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IWDP_SUCCESS ; 
 int /*<<< orphan*/  iwdp_ifs_free (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__) ; 

iwdp_status iwdp_ifs_close(iwdp_t self, iwdp_ifs_t ifs) {
  iwdp_iws_t iws = ifs->iws;
  // clear pointer to this ifs
  if (iws && iws->ifs == ifs) {
    iws->ifs = NULL;
  }
  iwdp_ifs_free(ifs);
  // close client
  if (iws && iws->ws_fd > 0) {
    self->remove_fd(self, iws->ws_fd);
  }
  return IWDP_SUCCESS;
}