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
struct TYPE_4__ {scalar_t__ state; struct TYPE_4__* next; struct TYPE_4__* prev; scalar_t__ end; scalar_t__ pptr; scalar_t__ wptr; scalar_t__ rptr; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 TYPE_1__ NB_Head ; 
 scalar_t__ NB_MAGIC_BUSY ; 
 scalar_t__ NB_MAGIC_BUSYHEAD ; 
 scalar_t__ NB_MAGIC_FREE ; 
 int /*<<< orphan*/  NB_free ; 
 int /*<<< orphan*/  NB_used ; 
 int /*<<< orphan*/  assert (int) ; 

int free_buffer (netbuffer_t *R) {
  netbuffer_t *S = NB_Head.next;
  assert (R->state == NB_MAGIC_BUSY || (R->state == NB_MAGIC_BUSYHEAD && R->prev == R && R->next == R));
  R->rptr = R->wptr = R->pptr = R->end = 0;
  R->state = NB_MAGIC_FREE;
  R->prev = &NB_Head;
  R->next = S;
  S->prev = R;
  NB_Head.next = R;
  NB_used--;
  NB_free++;
  return 0;
}