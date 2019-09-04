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
struct TYPE_5__ {struct TYPE_5__* prev; int /*<<< orphan*/  next; } ;
typedef  TYPE_1__ inst ;
struct TYPE_6__ {TYPE_1__* last; scalar_t__ first; } ;
typedef  TYPE_2__ block ;

/* Variables and functions */

__attribute__((used)) static inst* block_take_last(block* b) {
  inst* i = b->last;
  if (i == 0)
    return 0;
  if (i->prev) {
    i->prev->next = i->next;
    b->last = i->prev;
    i->prev = 0;
  } else {
    b->first = 0;
    b->last = 0;
  }
  return i;
}