#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct forth_stack {int /*<<< orphan*/  top; TYPE_1__* x; } ;
struct TYPE_2__ {int /*<<< orphan*/  a; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_type (struct forth_stack*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ft_int ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pop_int (struct forth_stack *st, int *i, char *who) {
  if (!check_type (st, ft_int, who)) {
    return 0;
  }
  memcpy (i, &st->x[st->top--].a, 4);
  return 1;
}