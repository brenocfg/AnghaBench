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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_diff_line_cb ;
typedef  int /*<<< orphan*/  git_diff_format_t ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_5__ {int old_lineno; int new_lineno; int num_lines; } ;
struct TYPE_4__ {scalar_t__ id_strlen; TYPE_2__ line; int /*<<< orphan*/ * buf; void* payload; int /*<<< orphan*/  print_cb; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ diff_print_info ;

/* Variables and functions */
 scalar_t__ GIT_ABBREV_DEFAULT ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_ABBREV ; 
 scalar_t__ GIT_OID_HEXSZ ; 
 scalar_t__ git_repository__configmap_lookup (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int diff_print_info_init__common(
	diff_print_info *pi,
	git_buf *out,
	git_repository *repo,
	git_diff_format_t format,
	git_diff_line_cb cb,
	void *payload)
{
	pi->format = format;
	pi->print_cb = cb;
	pi->payload = payload;
	pi->buf = out;

	if (!pi->id_strlen) {
		if (!repo)
			pi->id_strlen = GIT_ABBREV_DEFAULT;
		else if (git_repository__configmap_lookup(&pi->id_strlen, repo, GIT_CONFIGMAP_ABBREV) < 0)
			return -1;
	}

	if (pi->id_strlen > GIT_OID_HEXSZ)
		pi->id_strlen = GIT_OID_HEXSZ;

	memset(&pi->line, 0, sizeof(pi->line));
	pi->line.old_lineno = -1;
	pi->line.new_lineno = -1;
	pi->line.num_lines = 1;

	return 0;
}