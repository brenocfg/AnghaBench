#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct repository_format {int dummy; } ;
struct TYPE_2__ {int have_repository; } ;

/* Variables and functions */
 struct repository_format REPOSITORY_FORMAT_INIT ; 
 int /*<<< orphan*/  check_repository_format_gently (int /*<<< orphan*/ ,struct repository_format*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_repository_format (struct repository_format*) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 TYPE_1__* startup_info ; 

void check_repository_format(void)
{
	struct repository_format repo_fmt = REPOSITORY_FORMAT_INIT;
	check_repository_format_gently(get_git_dir(), &repo_fmt, NULL);
	startup_info->have_repository = 1;
	clear_repository_format(&repo_fmt);
}