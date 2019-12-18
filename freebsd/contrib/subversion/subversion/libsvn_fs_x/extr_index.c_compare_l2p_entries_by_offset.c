#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ offset; } ;
typedef  TYPE_1__ l2p_page_entry_t ;

/* Variables and functions */

__attribute__((used)) static int
compare_l2p_entries_by_offset(const l2p_page_entry_t *lhs,
                              const l2p_page_entry_t *rhs)
{
  return lhs->offset > rhs->offset ? 1
                                   : lhs->offset == rhs->offset ? 0 : -1;
}