#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {size_t len; } ;
struct TYPE_21__ {TYPE_8__* file; TYPE_5__ map; } ;
struct TYPE_16__ {size_t len; } ;
struct TYPE_19__ {TYPE_6__* file; TYPE_4__ map; } ;
struct TYPE_14__ {int flags; } ;
struct TYPE_15__ {TYPE_2__ diff_opts; TYPE_1__* delta; } ;
struct TYPE_12__ {TYPE_9__ nfile; TYPE_7__ ofile; TYPE_3__ base; } ;
typedef  TYPE_10__ git_patch_generated ;
struct TYPE_20__ {int /*<<< orphan*/  id; scalar_t__ size; } ;
struct TYPE_18__ {int /*<<< orphan*/  id; scalar_t__ size; } ;
struct TYPE_13__ {scalar_t__ status; int flags; } ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_UNMODIFIED ; 
 int GIT_DIFF_FLAG_BINARY ; 
 int GIT_DIFF_SHOW_BINARY ; 
 int /*<<< orphan*/  git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool patch_generated_diffable(git_patch_generated *patch)
{
	size_t olen, nlen;

	if (patch->base.delta->status == GIT_DELTA_UNMODIFIED)
		return false;

	/* if we've determined this to be binary (and we are not showing binary
	 * data) then we have skipped loading the map data.  instead, query the
	 * file data itself.
	 */
	if ((patch->base.delta->flags & GIT_DIFF_FLAG_BINARY) != 0 &&
		(patch->base.diff_opts.flags & GIT_DIFF_SHOW_BINARY) == 0) {
		olen = (size_t)patch->ofile.file->size;
		nlen = (size_t)patch->nfile.file->size;
	} else {
		olen = patch->ofile.map.len;
		nlen = patch->nfile.map.len;
	}

	/* if both sides are empty, files are identical */
	if (!olen && !nlen)
		return false;

	/* otherwise, check the file sizes and the oid */
	return (olen != nlen ||
		!git_oid_equal(&patch->ofile.file->id, &patch->nfile.file->id));
}