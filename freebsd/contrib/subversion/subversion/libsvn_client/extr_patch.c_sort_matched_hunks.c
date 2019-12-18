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
typedef  scalar_t__ svn_linenum_t ;
typedef  int svn_boolean_t ;
struct TYPE_2__ {scalar_t__ matched_line; int /*<<< orphan*/  hunk; int /*<<< orphan*/  already_applied; int /*<<< orphan*/  rejected; } ;
typedef  TYPE_1__ hunk_info_t ;

/* Variables and functions */
 scalar_t__ svn_diff_hunk_get_original_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sort_matched_hunks(const void *a, const void *b)
{
  const hunk_info_t *item1 = *((const hunk_info_t * const *)a);
  const hunk_info_t *item2 = *((const hunk_info_t * const *)b);
  svn_boolean_t matched1 = !item1->rejected && !item1->already_applied;
  svn_boolean_t matched2 = !item2->rejected && !item2->already_applied;
  svn_linenum_t original1, original2;

  if (matched1 && matched2)
    {
      /* Both match so use order matched in file. */
      if (item1->matched_line > item2->matched_line)
        return 1;
      else if (item1->matched_line == item2->matched_line)
        return 0;
      else
        return -1;
    }
  else if (matched2)
    /* Only second matches, put it before first. */
    return 1;
  else if (matched1)
    /* Only first matches, put it before second. */
    return -1;

  /* Neither matches, sort by original_start. */
  original1 = svn_diff_hunk_get_original_start(item1->hunk);
  original2 = svn_diff_hunk_get_original_start(item2->hunk);
  if (original1 > original2)
    return 1;
  else if (original1 == original2)
    return 0;
  else
    return -1;
}