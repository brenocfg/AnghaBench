#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct iwdp_struct {int dummy; } ;
struct iwdp_private {int dummy; } ;
typedef  TYPE_1__* iwdp_t ;
typedef  TYPE_1__* iwdp_private_t ;
struct TYPE_6__ {int /*<<< orphan*/  device_id_to_iport; int /*<<< orphan*/ * sim_wi_socket_addr; int /*<<< orphan*/ * frontend; struct TYPE_6__* private_state; int /*<<< orphan*/  on_error; int /*<<< orphan*/  on_close; int /*<<< orphan*/  on_recv; int /*<<< orphan*/  on_accept; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_STRING_KEYS ; 
 int /*<<< orphan*/  ht_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwdp_free (TYPE_1__*) ; 
 int /*<<< orphan*/  iwdp_on_accept ; 
 int /*<<< orphan*/  iwdp_on_close ; 
 int /*<<< orphan*/  iwdp_on_error ; 
 int /*<<< orphan*/  iwdp_on_recv ; 
 int /*<<< orphan*/  iwdp_start ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

iwdp_t iwdp_new(const char *frontend, const char *sim_wi_socket_addr) {
  iwdp_t self = (iwdp_t)malloc(sizeof(struct iwdp_struct));
  iwdp_private_t my = (iwdp_private_t)malloc(sizeof(struct iwdp_private));
  if (!self || !my) {
    iwdp_free(self);
    return NULL;
  }
  memset(self, 0, sizeof(struct iwdp_struct));
  memset(my, 0, sizeof(struct iwdp_private));
  self->start = iwdp_start;
  self->on_accept = iwdp_on_accept;
  self->on_recv = iwdp_on_recv;
  self->on_close = iwdp_on_close;
  self->on_error = iwdp_on_error;
  self->private_state = my;
  my->frontend = (frontend ? strdup(frontend) : NULL);
  my->sim_wi_socket_addr = strdup(sim_wi_socket_addr);
  my->device_id_to_iport = ht_new(HT_STRING_KEYS);
  if (!my->device_id_to_iport) {
    iwdp_free(self);
    return NULL;
  }
  return self;
}