#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  checkout_strategy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 int /*<<< orphan*/  GIT_CHECKOUT_OPTIONS_VERSION ; 
 int /*<<< orphan*/  GIT_INIT_STRUCTURE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ checkout_opts ; 
 int /*<<< orphan*/  cl_git_sandbox_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_name ; 

void test_checkout_nasty__initialize(void)
{
	repo = cl_git_sandbox_init(repo_name);

	GIT_INIT_STRUCTURE(&checkout_opts, GIT_CHECKOUT_OPTIONS_VERSION);
	checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE;
}