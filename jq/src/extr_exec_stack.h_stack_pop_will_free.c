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
struct stack {scalar_t__ limit; } ;
typedef  scalar_t__ stack_ptr ;

/* Variables and functions */

__attribute__((used)) static int stack_pop_will_free(struct stack* s, stack_ptr p) {
  return p == s->limit;
}