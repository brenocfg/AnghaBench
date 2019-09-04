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
struct TYPE_2__ {char* a; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_type (struct forth_stack*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ft_str ; 

__attribute__((used)) static int pop_str (struct forth_stack *st, char **i, char *who) {
  if (!check_type (st, ft_str, who)) {
    return 0;
  }
  *i = st->x[st->top--].a;
  return 1;
}