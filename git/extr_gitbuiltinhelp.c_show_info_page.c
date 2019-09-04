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

/* Variables and functions */
 int /*<<< orphan*/  GIT_INFO_PATH ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* cmd_to_page (char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execlp (char*,char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  setenv (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  system_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_info_page(const char *git_cmd)
{
	const char *page = cmd_to_page(git_cmd);
	setenv("INFOPATH", system_path(GIT_INFO_PATH), 1);
	execlp("info", "info", "gitman", page, (char *)NULL);
	die(_("no info viewer handled the request"));
}