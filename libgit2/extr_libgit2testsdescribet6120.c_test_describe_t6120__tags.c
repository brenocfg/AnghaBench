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
struct TYPE_4__ {int /*<<< orphan*/  describe_strategy; } ;
typedef  TYPE_1__ git_describe_options ;
typedef  int /*<<< orphan*/  git_describe_format_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DESCRIBE_FORMAT_OPTIONS_INIT ; 
 TYPE_1__ GIT_DESCRIBE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DESCRIBE_TAGS ; 
 int /*<<< orphan*/  assert_describe (char*,char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_describe_t6120__tags(void)
{
	git_describe_options opts = GIT_DESCRIBE_OPTIONS_INIT;
	git_describe_format_options fmt_opts = GIT_DESCRIBE_FORMAT_OPTIONS_INIT;
	opts.describe_strategy = GIT_DESCRIBE_TAGS;

	assert_describe("c-*", "HEAD", repo, &opts, &fmt_opts);
	assert_describe("c-*", "HEAD^", repo, &opts, &fmt_opts);
	assert_describe("e-*", "HEAD^^", repo, &opts, &fmt_opts);
	assert_describe("c-*", "HEAD^^2", repo, &opts, &fmt_opts);
	assert_describe("B", "HEAD^^2^", repo, &opts, &fmt_opts);
	assert_describe("e", "HEAD^^^", repo, &opts, &fmt_opts);
}