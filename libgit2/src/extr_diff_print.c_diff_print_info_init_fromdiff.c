#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_diff_line_cb ;
typedef  int /*<<< orphan*/  git_diff_format_t ;
struct TYPE_8__ {int /*<<< orphan*/  new_prefix; int /*<<< orphan*/  old_prefix; int /*<<< orphan*/  id_abbrev; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  strcomp; TYPE_1__ opts; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_2__ git_diff ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_10__ {int /*<<< orphan*/  strcomp; int /*<<< orphan*/  new_prefix; int /*<<< orphan*/  old_prefix; int /*<<< orphan*/  id_strlen; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ diff_print_info ;

/* Variables and functions */
 int diff_print_info_init__common (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int diff_print_info_init_fromdiff(
	diff_print_info *pi,
	git_buf *out,
	git_diff *diff,
	git_diff_format_t format,
	git_diff_line_cb cb,
	void *payload)
{
	git_repository *repo = diff ? diff->repo : NULL;

	memset(pi, 0, sizeof(diff_print_info));

	if (diff) {
		pi->flags = diff->opts.flags;
		pi->id_strlen = diff->opts.id_abbrev;
		pi->old_prefix = diff->opts.old_prefix;
		pi->new_prefix = diff->opts.new_prefix;

		pi->strcomp = diff->strcomp;
	}

	return diff_print_info_init__common(pi, out, repo, format, cb, payload);
}