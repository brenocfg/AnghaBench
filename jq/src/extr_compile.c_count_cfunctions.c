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
struct TYPE_4__ {scalar_t__ op; TYPE_2__ subfn; struct TYPE_4__* next; } ;
typedef  TYPE_1__ inst ;
typedef  TYPE_2__ block ;

/* Variables and functions */
 scalar_t__ CLOSURE_CREATE_C ; 

__attribute__((used)) static int count_cfunctions(block b) {
  int n = 0;
  for (inst* i = b.first; i; i = i->next) {
    if (i->op == CLOSURE_CREATE_C) n++;
    n += count_cfunctions(i->subfn);
  }
  return n;
}