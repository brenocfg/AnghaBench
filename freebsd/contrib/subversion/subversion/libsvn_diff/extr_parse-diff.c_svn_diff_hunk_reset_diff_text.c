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
struct TYPE_4__ {int /*<<< orphan*/  start; int /*<<< orphan*/  current; } ;
struct TYPE_5__ {TYPE_1__ diff_text_range; } ;
typedef  TYPE_2__ svn_diff_hunk_t ;

/* Variables and functions */

void
svn_diff_hunk_reset_diff_text(svn_diff_hunk_t *hunk)
{
  hunk->diff_text_range.current = hunk->diff_text_range.start;
}