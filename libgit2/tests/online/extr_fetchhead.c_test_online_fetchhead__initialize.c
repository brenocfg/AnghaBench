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
typedef  int /*<<< orphan*/  git_fetch_options ;
typedef  int /*<<< orphan*/  git_clone_options ;
struct TYPE_3__ {int /*<<< orphan*/  fetch_opts; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CLONE_OPTIONS_VERSION ; 
 int /*<<< orphan*/  GIT_FETCH_OPTIONS_INIT ; 
 TYPE_1__ g_options ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void test_online_fetchhead__initialize(void)
{
	git_fetch_options dummy_fetch = GIT_FETCH_OPTIONS_INIT;
	g_repo = NULL;

	memset(&g_options, 0, sizeof(git_clone_options));
	g_options.version = GIT_CLONE_OPTIONS_VERSION;
	g_options.fetch_opts = dummy_fetch;
}