#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct condition_filter_iterator {int /*<<< orphan*/  pos; TYPE_1__* A; int /*<<< orphan*/  Cond; int /*<<< orphan*/  (* jump_to ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* iterator_t ;
typedef  int /*<<< orphan*/  condition_t ;
struct TYPE_5__ {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  condition_filter_iterator_jump_to (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct condition_filter_iterator* zmalloc (int) ; 

iterator_t build_condition_filter_iterator (iterator_t A, condition_t Cond) {
  struct condition_filter_iterator *I = zmalloc (sizeof (struct condition_filter_iterator));
  I->jump_to = condition_filter_iterator_jump_to;
  I->Cond = Cond;
  I->A = A;
  I->pos = A->pos;
  condition_filter_iterator_jump_to ((iterator_t) I, A->pos);
  return (iterator_t) I;
}