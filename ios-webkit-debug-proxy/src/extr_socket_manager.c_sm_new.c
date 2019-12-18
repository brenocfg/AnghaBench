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
struct sm_struct {int dummy; } ;
typedef  TYPE_1__* sm_t ;
typedef  scalar_t__ sm_private_t ;
struct TYPE_4__ {scalar_t__ private_state; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  select; int /*<<< orphan*/  send; int /*<<< orphan*/  remove_fd; int /*<<< orphan*/  add_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sm_add_fd ; 
 int /*<<< orphan*/  sm_cleanup ; 
 int /*<<< orphan*/  sm_private_free (scalar_t__) ; 
 scalar_t__ sm_private_new (size_t) ; 
 int /*<<< orphan*/  sm_remove_fd ; 
 int /*<<< orphan*/  sm_select ; 
 int /*<<< orphan*/  sm_send ; 

sm_t sm_new(size_t buf_length) {
  sm_private_t my = sm_private_new(buf_length);
  if (!my) {
    return NULL;
  }
  sm_t self = (sm_t)malloc(sizeof(struct sm_struct));
  if (!self) {
    sm_private_free(my);
    return NULL;
  }
  memset(self, 0, sizeof(struct sm_struct));
  self->add_fd = sm_add_fd;
  self->remove_fd = sm_remove_fd;
  self->send = sm_send;
  self->select = sm_select;
  self->cleanup = sm_cleanup;
  self->private_state = my;
  return self;
}