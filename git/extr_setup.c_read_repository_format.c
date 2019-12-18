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
struct repository_format {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_repo_format ; 
 int /*<<< orphan*/  clear_repository_format (struct repository_format*) ; 
 int /*<<< orphan*/  git_config_from_file (int /*<<< orphan*/ ,char const*,struct repository_format*) ; 

int read_repository_format(struct repository_format *format, const char *path)
{
	clear_repository_format(format);
	git_config_from_file(check_repo_format, path, format);
	if (format->version == -1)
		clear_repository_format(format);
	return format->version;
}