#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* delta; } ;
struct TYPE_9__ {TYPE_3__ base; } ;
typedef  TYPE_4__ git_patch_parsed ;
typedef  int /*<<< orphan*/  git_patch_parse_ctx ;
struct TYPE_6__ {int /*<<< orphan*/  mode; int /*<<< orphan*/ * path; } ;
struct TYPE_7__ {int nfiles; TYPE_1__ old_file; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DELTA_DELETED ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int parse_header_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_header_git_deletedfilemode(
	git_patch_parsed *patch,
	git_patch_parse_ctx *ctx)
{
	git__free((char *)patch->base.delta->old_file.path);

	patch->base.delta->old_file.path = NULL;
	patch->base.delta->status = GIT_DELTA_DELETED;
	patch->base.delta->nfiles = 1;

	return parse_header_mode(&patch->base.delta->old_file.mode, ctx);
}