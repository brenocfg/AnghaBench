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
struct forth_stack {size_t top; TYPE_1__* x; int /*<<< orphan*/  error; } ;
struct TYPE_2__ {int tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,...) ; 
 char* type_to_string (int) ; 

__attribute__((used)) static int check_type (struct forth_stack *st, int tp_bitset, char *who) {
  if (st->top < 0) {
    snprintf (st->error, sizeof (st->error), "%s (stack underflow)", who);
    return 0;
  }
  if (!(st->x[st->top].tp & tp_bitset)) {
    snprintf (st->error, sizeof (st->error), "%s (%s type found instead of 0x%x type))", who, type_to_string (st->x[st->top].tp), tp_bitset);
    return 0;
  }
  return 1;
}