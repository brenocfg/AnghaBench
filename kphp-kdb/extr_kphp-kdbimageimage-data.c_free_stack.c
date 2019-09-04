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
struct forth_stack {int /*<<< orphan*/ * x; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_stack_entry (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_stack (struct forth_stack *st, int bottom, int top) {
  int i;
  for (i = bottom; i <= top; i++) {
    free_stack_entry (&st->x[i]);
  }
}