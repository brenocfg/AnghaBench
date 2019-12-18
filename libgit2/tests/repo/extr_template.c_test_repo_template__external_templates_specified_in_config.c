#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ git_repository_init_options ;

/* Variables and functions */
 int GIT_REPOSITORY_INIT_BARE ; 
 int GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE ; 
 int GIT_REPOSITORY_INIT_MKPATH ; 
 TYPE_1__ GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  setup_repo (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  setup_templates (char*,int) ; 
 int /*<<< orphan*/  validate_templates (int /*<<< orphan*/ ,char*) ; 

void test_repo_template__external_templates_specified_in_config(void)
{
	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;

	opts.flags = GIT_REPOSITORY_INIT_MKPATH | GIT_REPOSITORY_INIT_BARE |
		GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE;

	setup_templates("template", true);
	setup_repo("templated.git", &opts);

	validate_templates(_repo, "template");
}