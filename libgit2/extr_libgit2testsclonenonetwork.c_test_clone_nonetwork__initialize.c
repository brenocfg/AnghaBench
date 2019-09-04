#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_fetch_options ;
typedef  int /*<<< orphan*/  git_clone_options ;
struct TYPE_5__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;
struct TYPE_6__ {int /*<<< orphan*/  fetch_opts; TYPE_1__ checkout_opts; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_CLONE_OPTIONS_VERSION ; 
 int /*<<< orphan*/  GIT_FETCH_OPTIONS_INIT ; 
 TYPE_2__ g_options ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void test_clone_nonetwork__initialize(void)
{
	git_checkout_options dummy_opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_fetch_options dummy_fetch = GIT_FETCH_OPTIONS_INIT;

	g_repo = NULL;

	memset(&g_options, 0, sizeof(git_clone_options));
	g_options.version = GIT_CLONE_OPTIONS_VERSION;
	g_options.checkout_opts = dummy_opts;
	g_options.checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
	g_options.fetch_opts = dummy_fetch;
}