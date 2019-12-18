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
struct id_range_iterator {int lim; } ;
typedef  TYPE_1__* iterator_t ;
struct TYPE_3__ {int pos; int /*<<< orphan*/  jump_to; } ;

/* Variables and functions */
 int INFTY ; 
 scalar_t__* User ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  empty_iterator_jump_to ; 

int id_range_iterator_jump_to (iterator_t I, int req_pos) {
  assert (req_pos > I->pos);
  while (req_pos <= ((struct id_range_iterator *) I)->lim) {
    if (User[req_pos]) {
      return I->pos = req_pos;
    }
    ++req_pos;
  }
  I->jump_to = empty_iterator_jump_to;
  return I->pos = INFTY;
}