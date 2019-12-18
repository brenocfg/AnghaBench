#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pc_entry_struct {int dummy; } ;
typedef  TYPE_1__* pc_t ;
typedef  TYPE_2__* pc_entry_t ;
struct TYPE_6__ {char const* device_id; int min_port; int max_port; struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__* tail; TYPE_2__* head; } ;

/* Variables and functions */
 TYPE_2__* malloc (int) ; 

void pc_add(pc_t self, const char *device_id, int min_port, int max_port) {
  pc_entry_t e = malloc(sizeof(struct pc_entry_struct));
  e->device_id = device_id;
  e->min_port = min_port;
  e->max_port = max_port;
  e->next = NULL;
  if (self->tail) {
    self->tail->next = e;
  } else {
    self->head = e;
  }
  self->tail = e;
}