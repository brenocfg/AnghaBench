#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* iwdp_t ;
typedef  int /*<<< orphan*/  iwdp_status ;
typedef  TYPE_2__* iwdp_iws_t ;
typedef  TYPE_3__* iwdp_iport_t ;
typedef  TYPE_4__* iwdp_ipage_t ;
typedef  TYPE_5__* iwdp_ifs_t ;
typedef  int /*<<< orphan*/  ht_t ;
struct TYPE_15__ {scalar_t__ fs_fd; int /*<<< orphan*/ * iws; } ;
struct TYPE_14__ {TYPE_2__* iws; scalar_t__ sender_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  ws_id_to_iws; } ;
struct TYPE_12__ {char* ws_id; TYPE_5__* ifs; TYPE_3__* iport; TYPE_4__* ipage; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* remove_fd ) (TYPE_1__*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IWDP_SUCCESS ; 
 int /*<<< orphan*/  ht_get_value (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ht_remove (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iwdp_iws_free (TYPE_2__*) ; 
 int /*<<< orphan*/  iwdp_stop_devtools (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__) ; 

iwdp_status iwdp_iws_close(iwdp_t self, iwdp_iws_t iws) {
  // clear pointer to this iws
  iwdp_ipage_t ipage = iws->ipage;
  if (ipage) {
    if (ipage->sender_id && ipage->iws == iws) {
      iwdp_stop_devtools(ipage);
    } // else internal error?
  }
  iwdp_iport_t iport = iws->iport;
  if (iport) {
    ht_t iws_ht = iport->ws_id_to_iws;
    char *ws_id = iws->ws_id;
    iwdp_iws_t iws2 = (iwdp_iws_t)ht_get_value(iws_ht, ws_id);
    if (ws_id && iws2 == iws) {
      ht_remove(iws_ht, ws_id);
    } // else internal error?
  }
  iwdp_ifs_t ifs = iws->ifs;
  if (ifs) {
    ifs->iws = NULL;
    if (ifs->fs_fd > 0) {
      self->remove_fd(self, ifs->fs_fd);
    } // else internal error?
  }
  iwdp_iws_free(iws);
  return IWDP_SUCCESS;
}