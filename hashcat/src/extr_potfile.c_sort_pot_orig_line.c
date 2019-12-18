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
struct TYPE_2__ {scalar_t__ line_pos; } ;
typedef  TYPE_1__ pot_orig_line_entry_t ;

/* Variables and functions */

int sort_pot_orig_line (const void *v1, const void *v2)
{
  const pot_orig_line_entry_t *t1 = (const pot_orig_line_entry_t *) v1;
  const pot_orig_line_entry_t *t2 = (const pot_orig_line_entry_t *) v2;

  return t1->line_pos > t2->line_pos;
}