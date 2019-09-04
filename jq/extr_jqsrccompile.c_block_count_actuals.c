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
struct TYPE_4__ {int op; struct TYPE_4__* next; } ;
typedef  TYPE_1__ inst ;
struct TYPE_5__ {TYPE_1__* first; } ;
typedef  TYPE_2__ block ;

/* Variables and functions */
#define  CLOSURE_CREATE 130 
#define  CLOSURE_CREATE_C 129 
#define  CLOSURE_PARAM 128 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int block_count_actuals(block b) {
  int args = 0;
  for (inst* i = b.first; i; i = i->next) {
    switch (i->op) {
    default: assert(0 && "Unknown function type"); break;
    case CLOSURE_CREATE:
    case CLOSURE_PARAM:
    case CLOSURE_CREATE_C:
      args++;
      break;
    }
  }
  return args;
}