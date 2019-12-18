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
struct man_viewer_list {char* name; struct man_viewer_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 char* cmd_to_page (char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_viewer (char const*,char const*) ; 
 char* getenv (char*) ; 
 struct man_viewer_list* man_viewer_list ; 
 int /*<<< orphan*/  setup_man_path () ; 

__attribute__((used)) static void show_man_page(const char *git_cmd)
{
	struct man_viewer_list *viewer;
	const char *page = cmd_to_page(git_cmd);
	const char *fallback = getenv("GIT_MAN_VIEWER");

	setup_man_path();
	for (viewer = man_viewer_list; viewer; viewer = viewer->next)
	{
		exec_viewer(viewer->name, page); /* will return when unable */
	}
	if (fallback)
		exec_viewer(fallback, page);
	exec_viewer("man", page);
	die(_("no man viewer handled the request"));
}