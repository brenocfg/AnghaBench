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
struct diff_options {int /*<<< orphan*/  file; int /*<<< orphan*/  line_prefix_length; int /*<<< orphan*/  line_prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void graph_show_line_prefix(const struct diff_options *diffopt)
{
	if (!diffopt || !diffopt->line_prefix)
		return;

	fwrite(diffopt->line_prefix,
	       sizeof(char),
	       diffopt->line_prefix_length,
	       diffopt->file);
}