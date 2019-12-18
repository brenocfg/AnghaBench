#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* delta; } ;
struct TYPE_7__ {int /*<<< orphan*/  rename_old_path; TYPE_2__ base; } ;
typedef  TYPE_3__ git_patch_parsed ;
typedef  int /*<<< orphan*/  git_patch_parse_ctx ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DELTA_RENAMED ; 
 int parse_header_rename (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_header_renamefrom(
	git_patch_parsed *patch, git_patch_parse_ctx *ctx)
{
	patch->base.delta->status = GIT_DELTA_RENAMED;
	return parse_header_rename(&patch->rename_old_path, ctx);
}