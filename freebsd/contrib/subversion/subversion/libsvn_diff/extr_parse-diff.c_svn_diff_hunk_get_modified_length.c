#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_linenum_t ;
struct TYPE_5__ {int /*<<< orphan*/  modified_length; int /*<<< orphan*/  original_length; TYPE_1__* patch; } ;
typedef  TYPE_2__ svn_diff_hunk_t ;
struct TYPE_4__ {scalar_t__ reverse; } ;

/* Variables and functions */

svn_linenum_t
svn_diff_hunk_get_modified_length(const svn_diff_hunk_t *hunk)
{
  return hunk->patch->reverse ? hunk->original_length : hunk->modified_length;
}