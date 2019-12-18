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
struct intersection_condition_iterator {long cnt; int /*<<< orphan*/  Cond; TYPE_2__** A; } ;
typedef  TYPE_1__* iterator_t ;
struct TYPE_6__ {int pos; int (* jump_to ) (TYPE_2__*,int) ;} ;
struct TYPE_5__ {int pos; void* jump_to; } ;

/* Variables and functions */
 int INFTY ; 
 int /*<<< orphan*/ * User ; 
 void* empty_iterator_jump_to ; 
 int stub1 (TYPE_2__*,int) ; 
 int stub2 (TYPE_2__*,int) ; 
 scalar_t__ user_matches_condition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int multiple_intersection_with_condition_jump_to (iterator_t I, int req_pos) {
  struct intersection_condition_iterator *ICI = (struct intersection_condition_iterator *)I;
  long i, N = ICI->cnt;
  int x;
  while (1) {
    do {
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
      if (req_pos == INFTY) {
	I->jump_to = empty_iterator_jump_to;
	return I->pos = INFTY;
      }
    } while (i < N);
    if (user_matches_condition (User[x], ICI->Cond, x)) {
      break;
    }
    req_pos = x + 1;
  }
  return I->pos = x;
}