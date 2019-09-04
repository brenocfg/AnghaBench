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
struct grep_opt {scalar_t__ null_following_name; int /*<<< orphan*/  (* output ) (struct grep_opt*,char*,int) ;int /*<<< orphan*/ * colors; } ;

/* Variables and functions */
 size_t GREP_COLOR_FILENAME ; 
 int /*<<< orphan*/  output_color (struct grep_opt*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct grep_opt*,char*,int) ; 

__attribute__((used)) static void show_name(struct grep_opt *opt, const char *name)
{
	output_color(opt, name, strlen(name), opt->colors[GREP_COLOR_FILENAME]);
	opt->output(opt, opt->null_following_name ? "\0" : "\n", 1);
}