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
struct pc_entry_struct {int dummy; } ;
typedef  TYPE_1__* pc_t ;
typedef  TYPE_2__* pc_entry_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
struct TYPE_6__ {int /*<<< orphan*/ * tail; TYPE_2__* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void pc_clear(pc_t self) {
  if (self) {
    pc_entry_t e = self->head;
    while (e) {
      pc_entry_t next = e->next;
      memset(e, 0, sizeof(struct pc_entry_struct));
      free(e);
      e = next;
    }
    self->head = NULL;
    self->tail = NULL;
  }
}