#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  send_queue_len; } ;
struct TYPE_7__ {int /*<<< orphan*/ * tid; TYPE_1__* prev; struct TYPE_7__* next; TYPE_2__ u; } ;
typedef  TYPE_3__ tftp_connection_t ;
struct TYPE_5__ {TYPE_3__* next; } ;

/* Variables and functions */
 TYPE_3__ completed_connections ; 
 int /*<<< orphan*/  get_connection_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 
 size_t working_mode ; 

__attribute__((used)) static void tftp_clean_completed_connections (void) {
  tftp_connection_t *c, *w;
  for (c = completed_connections.next; c != &completed_connections; c = w) {
    w = c->next;
    if (!c->u.send_queue_len) {
      c->prev->next = c->next;
      c->next->prev = c->prev;
      vkprintf (1, "Remove listening connection for port %d.\n", c->tid[working_mode]);
      get_connection_f (c->tid[working_mode], -1);
    }
  }
}