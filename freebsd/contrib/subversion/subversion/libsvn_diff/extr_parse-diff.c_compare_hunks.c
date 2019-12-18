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
struct TYPE_2__ {scalar_t__ original_start; } ;
typedef  TYPE_1__ svn_diff_hunk_t ;

/* Variables and functions */

__attribute__((used)) static int
compare_hunks(const void *a, const void *b)
{
  const svn_diff_hunk_t *ha = *((const svn_diff_hunk_t *const *)a);
  const svn_diff_hunk_t *hb = *((const svn_diff_hunk_t *const *)b);

  if (ha->original_start < hb->original_start)
    return -1;
  if (ha->original_start > hb->original_start)
    return 1;
  return 0;
}