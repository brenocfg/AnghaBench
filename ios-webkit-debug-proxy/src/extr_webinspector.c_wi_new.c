#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* wi_t ;
struct wi_struct {int dummy; } ;
struct TYPE_7__ {int partials_supported; } ;
struct TYPE_6__ {TYPE_2__* private_state; int /*<<< orphan*/  on_error; int /*<<< orphan*/  recv_packet; int /*<<< orphan*/  send_plist; int /*<<< orphan*/  on_recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  wi_on_error ; 
 int /*<<< orphan*/  wi_on_recv ; 
 TYPE_2__* wi_private_new () ; 
 int /*<<< orphan*/  wi_recv_packet ; 
 int /*<<< orphan*/  wi_send_plist ; 

wi_t wi_new(bool partials_supported) {
  wi_t self = (wi_t)malloc(sizeof(struct wi_struct));
  if (!self) {
    return NULL;
  }
  memset(self, 0, sizeof(struct wi_struct));
  self->on_recv = wi_on_recv;
  self->send_plist = wi_send_plist;
  self->recv_packet = wi_recv_packet;
  self->on_error = wi_on_error;
  self->private_state = wi_private_new();
  if (!self->private_state) {
    wi_free(self);
    return NULL;
  }
  self->private_state->partials_supported = partials_supported;
  return self;
}