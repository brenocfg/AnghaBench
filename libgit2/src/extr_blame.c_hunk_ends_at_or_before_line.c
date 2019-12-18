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
struct TYPE_3__ {int final_start_line_number; int lines_in_hunk; } ;
typedef  TYPE_1__ git_blame_hunk ;

/* Variables and functions */

__attribute__((used)) static bool hunk_ends_at_or_before_line(git_blame_hunk *hunk, size_t line)
{
	return line >= (hunk->final_start_line_number + hunk->lines_in_hunk - 1);
}