#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct binary_operation_iterator {int pos; int /*<<< orphan*/  jump_to; TYPE_1__* A; } ;
typedef  scalar_t__ iterator_t ;
struct TYPE_2__ {int (* jump_to ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int INFTY ; 
 int /*<<< orphan*/  empty_iterator_jump_to ; 
 int stub1 (TYPE_1__*,int) ; 

int dummy_iterator_jump_to (iterator_t I, int req_pos) {
  struct binary_operation_iterator *X = (struct binary_operation_iterator *) I;
  int res = X->A->jump_to (X->A, req_pos);
  if (res == INFTY) {
    X->jump_to = empty_iterator_jump_to;
  }
  return X->pos = res;
}