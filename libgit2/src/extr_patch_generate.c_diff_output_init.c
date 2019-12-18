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
struct TYPE_4__ {void* payload; int /*<<< orphan*/  data_cb; int /*<<< orphan*/  hunk_cb; int /*<<< orphan*/  binary_cb; int /*<<< orphan*/  file_cb; } ;
typedef  TYPE_1__ git_patch_generated_output ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff_line_cb ;
typedef  int /*<<< orphan*/  git_diff_hunk_cb ;
typedef  int /*<<< orphan*/  git_diff_file_cb ;
typedef  int /*<<< orphan*/  git_diff_binary_cb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void diff_output_init(
	git_patch_generated_output *out,
	const git_diff_options *opts,
	git_diff_file_cb file_cb,
	git_diff_binary_cb binary_cb,
	git_diff_hunk_cb hunk_cb,
	git_diff_line_cb data_cb,
	void *payload)
{
	GIT_UNUSED(opts);

	memset(out, 0, sizeof(*out));

	out->file_cb = file_cb;
	out->binary_cb = binary_cb;
	out->hunk_cb = hunk_cb;
	out->data_cb = data_cb;
	out->payload = payload;
}