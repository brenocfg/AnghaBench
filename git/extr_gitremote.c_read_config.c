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
struct TYPE_2__ {scalar_t__ have_repository; } ;

/* Variables and functions */
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  alias_all_urls () ; 
 int /*<<< orphan*/ * current_branch ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_config ; 
 int /*<<< orphan*/ * make_branch (char const*,int /*<<< orphan*/ ) ; 
 char* resolve_ref_unsafe (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 TYPE_1__* startup_info ; 

__attribute__((used)) static void read_config(void)
{
	static int loaded;
	int flag;

	if (loaded)
		return;
	loaded = 1;

	current_branch = NULL;
	if (startup_info->have_repository) {
		const char *head_ref = resolve_ref_unsafe("HEAD", 0, NULL, &flag);
		if (head_ref && (flag & REF_ISSYMREF) &&
		    skip_prefix(head_ref, "refs/heads/", &head_ref)) {
			current_branch = make_branch(head_ref, 0);
		}
	}
	git_config(handle_config, NULL);
	alias_all_urls();
}