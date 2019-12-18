#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  header_len; int /*<<< orphan*/  header; } ;
typedef  TYPE_2__ git_diff_hunk ;
struct TYPE_10__ {int /*<<< orphan*/  mode; } ;
struct TYPE_12__ {TYPE_1__ new_file; } ;
typedef  TYPE_3__ git_diff_delta ;
struct TYPE_14__ {int /*<<< orphan*/  content_len; int /*<<< orphan*/  content; int /*<<< orphan*/  origin; } ;
struct TYPE_13__ {int (* print_cb ) (TYPE_3__ const*,TYPE_2__ const*,TYPE_7__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; TYPE_7__ line; } ;
typedef  TYPE_4__ diff_print_info ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_LINE_HUNK_HDR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__ const*,TYPE_2__ const*,TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diff_print_patch_hunk(
	const git_diff_delta *d,
	const git_diff_hunk *h,
	void *data)
{
	diff_print_info *pi = data;

	if (S_ISDIR(d->new_file.mode))
		return 0;

	pi->line.origin      = GIT_DIFF_LINE_HUNK_HDR;
	pi->line.content     = h->header;
	pi->line.content_len = h->header_len;

	return pi->print_cb(d, h, &pi->line, pi->payload);
}