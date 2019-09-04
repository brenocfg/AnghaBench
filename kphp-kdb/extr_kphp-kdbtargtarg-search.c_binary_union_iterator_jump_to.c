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
struct binary_operation_iterator {int pos; void* jump_to; TYPE_1__* B; TYPE_1__* A; } ;
typedef  scalar_t__ iterator_t ;
struct TYPE_3__ {int pos; int (* jump_to ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int INFTY ; 
 void* dummy_iterator_jump_to ; 
 void* empty_iterator_jump_to ; 
 int stub1 (TYPE_1__*,int) ; 
 int stub2 (TYPE_1__*,int) ; 

int binary_union_iterator_jump_to (iterator_t I, int req_pos) {
  struct binary_operation_iterator *X = (struct binary_operation_iterator *) I;
  int a = X->A->pos;
  int b = X->B->pos;
  if (a < req_pos) {
    a = X->A->jump_to (X->A, req_pos);
  }
  if (b < req_pos) {
    b = X->B->jump_to (X->B, req_pos);
  }
  if (a < b) {
    if (b == INFTY) {
      X->jump_to = dummy_iterator_jump_to;
    }
    return X->pos = a;
  } else if (a > b) {
    if (a == INFTY) {
      X->jump_to = dummy_iterator_jump_to;
      X->A = X->B;
    }
    return X->pos = b;
  } else {
    if (a == INFTY) {
      X->jump_to = empty_iterator_jump_to;
    }
    return X->pos = a;
  }
}