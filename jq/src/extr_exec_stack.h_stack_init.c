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
struct stack {scalar_t__ limit; int /*<<< orphan*/  bound; scalar_t__ mem_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGNMENT ; 

__attribute__((used)) static void stack_init(struct stack* s) {
  s->mem_end = 0;
  s->bound = ALIGNMENT;
  s->limit = 0;
}