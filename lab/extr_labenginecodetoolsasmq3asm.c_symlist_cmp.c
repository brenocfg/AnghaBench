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
struct TYPE_2__ {int value; } ;
typedef  TYPE_1__ symbol_t ;

/* Variables and functions */

__attribute__((used)) static int symlist_cmp (const void *e1, const void *e2)
{
  const symbol_t *a, *b;

  a = *(const symbol_t **)e1;
  b = *(const symbol_t **)e2;
//crumb("Symbol comparison (1) %d  to  (2) %d\n", a->value, b->value);
  return ( a->value - b->value);
}