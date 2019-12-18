#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct explicit_list_iterator {int pos; int* cur; int* last; void* jump_to; } ;
typedef  scalar_t__ iterator_t ;

/* Variables and functions */
 int INFTY ; 
 int /*<<< orphan*/  assert (int) ; 
 void* empty_iterator_jump_to ; 

int explicit_list_iterator_jump_to (iterator_t I, int req_pos) {
  struct explicit_list_iterator *IL = (struct explicit_list_iterator *) I;
  assert (req_pos > IL->pos);
  if (IL->cur == IL->last) {
    IL->jump_to = empty_iterator_jump_to;
    return IL->pos = INFTY;
  }
  if (req_pos <= *IL->cur) {
    return IL->pos = *(IL->cur++);
  }
  int *A = IL->cur;
  long a = 0, b = 1, c = IL->last - A;
  if (b < c) {
    while (A[b] < req_pos) {  // a < b < c, A[a] < req_pos
      a = b;
      b <<= 1;
      if (b >= c) {
	b = c;
	break;
      }
    }
  }
  // A[a] < req_pos <= A[b] , 0 <= a < b <= c
  while (b - a > 1) {
    c = (a + b) >> 1;
    if (A[c] < req_pos) {
      a = c;
    } else {
      b = c;
    }
  }
  A += b;
  if (A == IL->last) {
    IL->cur = A;
    IL->jump_to = empty_iterator_jump_to;
    return IL->pos = INFTY;
  }
  IL->cur = A + 1;
  return IL->pos = *A;
}