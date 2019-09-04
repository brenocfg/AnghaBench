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
struct iterator {int pos; int /*<<< orphan*/  (* jump_to ) (struct iterator*,int /*<<< orphan*/ ) ;} ;
typedef  struct iterator* iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  everything_iterator_jump_to (struct iterator*,int /*<<< orphan*/ ) ; 
 struct iterator* zmalloc (int) ; 

iterator_t build_everything_iterator (void) {
  struct iterator *I = zmalloc (sizeof (struct iterator));
  I->jump_to = everything_iterator_jump_to;
  I->pos = -1;
  everything_iterator_jump_to (I, 0);
  return I;
}