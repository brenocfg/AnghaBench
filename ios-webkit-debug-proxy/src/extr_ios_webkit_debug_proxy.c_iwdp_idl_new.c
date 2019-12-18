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
struct iwdp_idl_struct {int dummy; } ;
typedef  TYPE_2__* iwdp_idl_t ;
typedef  TYPE_3__* dl_t ;
struct TYPE_10__ {TYPE_2__* state; int /*<<< orphan*/  on_detach; int /*<<< orphan*/  on_attach; int /*<<< orphan*/  send_packet; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {TYPE_3__* dl; TYPE_1__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_IDL ; 
 TYPE_3__* dl_new () ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  iwdp_on_attach ; 
 int /*<<< orphan*/  iwdp_on_detach ; 
 int /*<<< orphan*/  iwdp_send_to_dl ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

iwdp_idl_t iwdp_idl_new() {
  iwdp_idl_t idl = (iwdp_idl_t)malloc(sizeof(struct iwdp_idl_struct));
  dl_t dl = dl_new();
  if (!idl || !dl) {
    free(idl);
    return NULL;
  }
  memset(idl, 0, sizeof(struct iwdp_idl_struct));
  idl->type.type = TYPE_IDL;
  idl->dl = dl;
  dl->send_packet = iwdp_send_to_dl;
  dl->on_attach = iwdp_on_attach;
  dl->on_detach = iwdp_on_detach;
  dl->state = idl;
  return idl;
}