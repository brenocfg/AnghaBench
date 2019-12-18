#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  TYPE_1__* cb_t ;
struct TYPE_4__ {char const* tail; char const* head; char const* in_head; char const* in_tail; int /*<<< orphan*/  begin; } ;

/* Variables and functions */
 scalar_t__ cb_ensure_capacity (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char const*,char const*,scalar_t__) ; 

int cb_begin_input(cb_t self, const char *buf, ssize_t length) {
  if (!buf || length < 0) {
    return -1;
  }
  // Instead of always doing a memcpy into our buffer, see if we can
  // use the buf as-is
  int can_share = (!self->begin || self->tail == self->head);
  if (can_share) {
    self->in_head = buf;
    self->in_tail = buf + length;
  } else {
    if (cb_ensure_capacity(self, length)) {
      return -1;
    }
    if (length > 0) {
      memcpy(self->tail, buf, length);
      self->tail += length;
    }
    self->in_head = self->head;
    self->in_tail = self->tail;
  }
  return 0;
}