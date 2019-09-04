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
struct intersection_condition_iterator {int cnt; TYPE_2__** A; } ;
typedef  TYPE_1__* iterator_t ;
struct TYPE_7__ {int pos; int (* jump_to ) (TYPE_2__*,int) ;} ;
struct TYPE_6__ {int pos; void* jump_to; } ;

/* Variables and functions */
 int INFTY ; 
 void* empty_iterator_jump_to ; 
 void* multiple_intersection_jump_to ; 
 int stub1 (TYPE_2__*,int) ; 
 int stub2 (TYPE_2__*,int) ; 
 int stub3 (TYPE_2__*,int) ; 

int multiple_intersection_subtraction_jump_to (iterator_t I, int req_pos) {
  struct intersection_condition_iterator *ICI = (struct intersection_condition_iterator *)I;
  long i, N = ICI->cnt - 1;
  int x;
  while (1) {
    x = ICI->A[0]->pos;
    if (x < req_pos) {
      x = ICI->A[0]->jump_to (ICI->A[0], req_pos);
    }
    if (x == INFTY) {
      I->jump_to = empty_iterator_jump_to;
      return I->pos = INFTY;
    }
    for (i = 1; i < N; i++) {
      req_pos = ICI->A[i]->pos;
      if (req_pos < x) {
	req_pos = ICI->A[i]->jump_to (ICI->A[i], x);
      }
      if (req_pos > x) {
	break;
      }
    }
    if (i < N) {
      if (req_pos == INFTY) {
	I->jump_to = empty_iterator_jump_to;
	return I->pos = INFTY;
      }
      continue;
    }
    req_pos = ICI->A[i]->pos;
    if (req_pos < x) {
      req_pos = ICI->A[i]->jump_to (ICI->A[i], x);
    }
    if (req_pos == INFTY) {
      ICI->cnt--;
      I->jump_to = multiple_intersection_jump_to;
      return I->pos = x;
    }
    if (req_pos != x) {
      return I->pos = x;
    }
    ++req_pos;
  }
}