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
typedef  int /*<<< orphan*/  git_patch_generated_output ;
typedef  int /*<<< orphan*/  git_patch_generated ;

/* Variables and functions */
 int /*<<< orphan*/  diff_output_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_hunk_cb ; 
 int /*<<< orphan*/  patch_generated_binary_cb ; 
 int /*<<< orphan*/  patch_generated_file_cb ; 
 int /*<<< orphan*/  patch_generated_line_cb ; 

__attribute__((used)) static void diff_output_to_patch(
	git_patch_generated_output *out, git_patch_generated *patch)
{
	diff_output_init(
		out,
		NULL,
		patch_generated_file_cb,
		patch_generated_binary_cb,
		git_patch_hunk_cb,
		patch_generated_line_cb,
		patch);
}