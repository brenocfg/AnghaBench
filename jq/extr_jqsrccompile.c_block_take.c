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
struct TYPE_5__ {struct TYPE_5__* next; scalar_t__ prev; } ;
typedef  TYPE_1__ inst ;
struct TYPE_6__ {scalar_t__ last; TYPE_1__* first; } ;
typedef  TYPE_2__ block ;

/* Variables and functions */

__attribute__((used)) static inst* block_take(block* b) {
  if (b->first == 0) return 0;
  inst* i = b->first;
  if (i->next) {
    i->next->prev = 0;
    b->first = i->next;
    i->next = 0;
  } else {
    b->first = 0;
    b->last = 0;
  }
  return i;
}