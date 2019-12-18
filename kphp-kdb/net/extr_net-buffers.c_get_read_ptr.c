#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ state; scalar_t__ rptr; scalar_t__ wptr; scalar_t__ pptr; struct TYPE_3__* next; } ;
typedef  TYPE_1__ netbuffer_t ;

/* Variables and functions */
 scalar_t__ NB_MAGIC_BUSYHEAD ; 
 scalar_t__ NB_MAGIC_HEAD ; 
 int /*<<< orphan*/  assert (int) ; 

char *get_read_ptr (netbuffer_t *H) {
  assert (H->state == NB_MAGIC_HEAD || H->state == NB_MAGIC_BUSYHEAD);
  if (H->rptr < H->wptr) {
    return H->rptr != H->pptr ? H->rptr : 0;
  }
  netbuffer_t *X = H->next;
  if (X != H && X->rptr < (X->pptr ? X->pptr : X->wptr)) {
    return X->rptr;
  }
  return 0;
}