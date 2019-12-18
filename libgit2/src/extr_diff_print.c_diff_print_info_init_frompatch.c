#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  new_prefix; int /*<<< orphan*/  old_prefix; int /*<<< orphan*/  id_abbrev; int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  repo; TYPE_1__ diff_opts; } ;
typedef  TYPE_2__ git_patch ;
typedef  int /*<<< orphan*/  git_diff_line_cb ;
typedef  int /*<<< orphan*/  git_diff_format_t ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_11__ {int /*<<< orphan*/  new_prefix; int /*<<< orphan*/  old_prefix; int /*<<< orphan*/  id_strlen; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ diff_print_info ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int diff_print_info_init__common (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int diff_print_info_init_frompatch(
	diff_print_info *pi,
	git_buf *out,
	git_patch *patch,
	git_diff_format_t format,
	git_diff_line_cb cb,
	void *payload)
{
	assert(patch);

	memset(pi, 0, sizeof(diff_print_info));

	pi->flags = patch->diff_opts.flags;
	pi->id_strlen = patch->diff_opts.id_abbrev;
	pi->old_prefix = patch->diff_opts.old_prefix;
	pi->new_prefix = patch->diff_opts.new_prefix;

	return diff_print_info_init__common(pi, out, patch->repo, format, cb, payload);
}