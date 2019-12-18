#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  start; int /*<<< orphan*/  current; } ;
struct TYPE_7__ {int /*<<< orphan*/  start; int /*<<< orphan*/  current; } ;
struct TYPE_9__ {TYPE_3__ original_text_range; TYPE_2__ modified_text_range; TYPE_1__* patch; } ;
typedef  TYPE_4__ svn_diff_hunk_t ;
struct TYPE_6__ {scalar_t__ reverse; } ;

/* Variables and functions */

void
svn_diff_hunk_reset_original_text(svn_diff_hunk_t *hunk)
{
  if (hunk->patch->reverse)
    hunk->modified_text_range.current = hunk->modified_text_range.start;
  else
    hunk->original_text_range.current = hunk->original_text_range.start;
}