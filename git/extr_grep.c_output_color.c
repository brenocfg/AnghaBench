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
struct grep_opt {int /*<<< orphan*/  (* output ) (struct grep_opt*,void const*,size_t) ;int /*<<< orphan*/  color; } ;

/* Variables and functions */
 char const* GIT_COLOR_RESET ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct grep_opt*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct grep_opt*,void const*,size_t) ; 
 int /*<<< orphan*/  stub3 (struct grep_opt*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct grep_opt*,void const*,size_t) ; 
 scalar_t__ want_color (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void output_color(struct grep_opt *opt, const void *data, size_t size,
			 const char *color)
{
	if (want_color(opt->color) && color && color[0]) {
		opt->output(opt, color, strlen(color));
		opt->output(opt, data, size);
		opt->output(opt, GIT_COLOR_RESET, strlen(GIT_COLOR_RESET));
	} else
		opt->output(opt, data, size);
}