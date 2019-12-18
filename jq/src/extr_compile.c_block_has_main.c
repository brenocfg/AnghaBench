#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ op; struct TYPE_4__* next; } ;
typedef  TYPE_1__ inst ;
struct TYPE_5__ {TYPE_1__* first; } ;
typedef  TYPE_2__ block ;

/* Variables and functions */
 scalar_t__ TOP ; 

int block_has_main(block top) {
  for (inst *c = top.first; c; c = c->next) {
    if (c->op == TOP)
      return 1;
  }
  return 0;
}