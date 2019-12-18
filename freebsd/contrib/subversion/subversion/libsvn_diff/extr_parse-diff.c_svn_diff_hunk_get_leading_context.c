#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_linenum_t ;
struct TYPE_3__ {int /*<<< orphan*/  leading_context; } ;
typedef  TYPE_1__ svn_diff_hunk_t ;

/* Variables and functions */

svn_linenum_t
svn_diff_hunk_get_leading_context(const svn_diff_hunk_t *hunk)
{
  return hunk->leading_context;
}