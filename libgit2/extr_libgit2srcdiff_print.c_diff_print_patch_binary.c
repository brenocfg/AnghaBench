#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff_binary ;
struct TYPE_5__ {int /*<<< orphan*/  content_len; int /*<<< orphan*/  content; int /*<<< orphan*/  origin; } ;
struct TYPE_4__ {char* old_prefix; char* new_prefix; int (* print_cb ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; TYPE_2__ line; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ diff_print_info ;

/* Variables and functions */
 char* DIFF_NEW_PREFIX_DEFAULT ; 
 char* DIFF_OLD_PREFIX_DEFAULT ; 
 int /*<<< orphan*/  GIT_DIFF_LINE_BINARY ; 
 int diff_print_patch_file_binary (TYPE_1__*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_len (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diff_print_patch_binary(
	const git_diff_delta *delta,
	const git_diff_binary *binary,
	void *data)
{
	diff_print_info *pi = data;
	const char *old_pfx =
		pi->old_prefix ? pi->old_prefix : DIFF_OLD_PREFIX_DEFAULT;
	const char *new_pfx =
		pi->new_prefix ? pi->new_prefix : DIFF_NEW_PREFIX_DEFAULT;
	int error;

	git_buf_clear(pi->buf);

	if ((error = diff_print_patch_file_binary(
		pi, (git_diff_delta *)delta, old_pfx, new_pfx, binary)) < 0)
		return error;

	pi->line.origin = GIT_DIFF_LINE_BINARY;
	pi->line.content = git_buf_cstr(pi->buf);
	pi->line.content_len = git_buf_len(pi->buf);

	return pi->print_cb(delta, NULL, &pi->line, pi->payload);
}