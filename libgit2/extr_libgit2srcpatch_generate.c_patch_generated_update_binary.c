#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_5__* delta; } ;
struct TYPE_12__ {TYPE_3__* file; } ;
struct TYPE_10__ {TYPE_1__* file; } ;
struct TYPE_15__ {TYPE_6__ base; TYPE_4__ nfile; TYPE_2__ ofile; } ;
typedef  TYPE_7__ git_patch_generated ;
struct TYPE_13__ {int flags; } ;
struct TYPE_11__ {int flags; scalar_t__ size; } ;
struct TYPE_9__ {int flags; scalar_t__ size; } ;

/* Variables and functions */
 int DIFF_FLAGS_KNOWN_BINARY ; 
 int DIFF_FLAGS_NOT_BINARY ; 
 int GIT_DIFF_FLAG_BINARY ; 
 int GIT_DIFF_FLAG_NOT_BINARY ; 
 scalar_t__ GIT_XDIFF_MAX_SIZE ; 

__attribute__((used)) static void patch_generated_update_binary(git_patch_generated *patch)
{
	if ((patch->base.delta->flags & DIFF_FLAGS_KNOWN_BINARY) != 0)
		return;

	if ((patch->ofile.file->flags & GIT_DIFF_FLAG_BINARY) != 0 ||
		(patch->nfile.file->flags & GIT_DIFF_FLAG_BINARY) != 0)
		patch->base.delta->flags |= GIT_DIFF_FLAG_BINARY;

	else if (patch->ofile.file->size > GIT_XDIFF_MAX_SIZE ||
		patch->nfile.file->size > GIT_XDIFF_MAX_SIZE)
		patch->base.delta->flags |= GIT_DIFF_FLAG_BINARY;

	else if ((patch->ofile.file->flags & DIFF_FLAGS_NOT_BINARY) != 0 &&
		(patch->nfile.file->flags & DIFF_FLAGS_NOT_BINARY) != 0)
		patch->base.delta->flags |= GIT_DIFF_FLAG_NOT_BINARY;
}