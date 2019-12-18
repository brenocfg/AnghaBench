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
struct fcb_table_entry {scalar_t__ p; scalar_t__ i; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_fcb_table_entry (const void *a, const void *b) {
  const struct fcb_table_entry *x = a;
  const struct fcb_table_entry *y = b;
  if (x->p < y->p) { return -1; }
  if (x->p > y->p) { return  1; }
  if (x->i < y->i) { return -1; }
  if (x->i > y->i) { return  1; }
  return 0;
}