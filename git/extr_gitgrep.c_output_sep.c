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
struct grep_opt {int /*<<< orphan*/ * colors; int /*<<< orphan*/  (* output ) (struct grep_opt*,char*,int) ;scalar_t__ null_following_name; } ;

/* Variables and functions */
 size_t GREP_COLOR_SEP ; 
 int /*<<< orphan*/  output_color (struct grep_opt*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct grep_opt*,char*,int) ; 

__attribute__((used)) static void output_sep(struct grep_opt *opt, char sign)
{
	if (opt->null_following_name)
		opt->output(opt, "\0", 1);
	else
		output_color(opt, &sign, 1, opt->colors[GREP_COLOR_SEP]);
}