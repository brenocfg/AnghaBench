#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  const* git_config_level_t ;
typedef  int /*<<< orphan*/  git_config_entries ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_7__ {int /*<<< orphan*/ * entries; } ;
struct TYPE_8__ {TYPE_1__ header; TYPE_4__* snapshot_from; } ;
typedef  TYPE_2__ diskfile_readonly_backend ;
struct TYPE_11__ {int /*<<< orphan*/  readonly; } ;
struct TYPE_9__ {TYPE_6__ parent; } ;
typedef  TYPE_3__ diskfile_header ;
struct TYPE_10__ {TYPE_3__ header; } ;
typedef  TYPE_4__ diskfile_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int config_refresh (TYPE_6__*) ; 
 int /*<<< orphan*/ * diskfile_entries_take (TYPE_3__*) ; 

__attribute__((used)) static int config_readonly_open(git_config_backend *cfg, git_config_level_t level, const git_repository *repo)
{
	diskfile_readonly_backend *b = (diskfile_readonly_backend *) cfg;
	diskfile_backend *src = b->snapshot_from;
	diskfile_header *src_header = &src->header;
	git_config_entries *entries;
	int error;

	if (!src_header->parent.readonly && (error = config_refresh(&src_header->parent)) < 0)
		return error;

	/* We're just copying data, don't care about the level or repo*/
	GIT_UNUSED(level);
	GIT_UNUSED(repo);

	if ((entries = diskfile_entries_take(src_header)) == NULL)
		return -1;
	b->header.entries = entries;

	return 0;
}