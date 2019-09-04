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
struct stack {scalar_t__ mem_end; } ;
typedef  scalar_t__ stack_ptr ;

/* Variables and functions */

__attribute__((used)) static void* stack_block(struct stack* s, stack_ptr p) {
  return (void*)(s->mem_end + p);
}