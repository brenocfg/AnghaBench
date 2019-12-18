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
struct blame_scoreboard {int num_lines; int /*<<< orphan*/  final_buf_size; int /*<<< orphan*/  final_buf; int /*<<< orphan*/  lineno; } ;

/* Variables and functions */
 int find_line_starts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prepare_lines(struct blame_scoreboard *sb)
{
	sb->num_lines = find_line_starts(&sb->lineno, sb->final_buf,
					 sb->final_buf_size);
	return sb->num_lines;
}