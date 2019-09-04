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
struct TYPE_5__ {TYPE_1__* first; } ;
typedef  TYPE_2__ block ;
struct TYPE_4__ {scalar_t__ op; } ;

/* Variables and functions */
 scalar_t__ CLOSURE_CREATE ; 

int block_is_funcdef(block b) {
  if (b.first != NULL && b.first->op == CLOSURE_CREATE)
    return 1;
  return 0;
}