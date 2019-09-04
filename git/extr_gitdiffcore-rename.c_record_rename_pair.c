#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct diff_filespec {int /*<<< orphan*/  path; int /*<<< orphan*/  count; int /*<<< orphan*/  rename_used; } ;
struct diff_filepair {int renamed_pair; int score; } ;
struct TYPE_6__ {struct diff_filepair* pair; struct diff_filespec* two; } ;
struct TYPE_5__ {int score; TYPE_1__* p; } ;
struct TYPE_4__ {struct diff_filespec* one; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 struct diff_filepair* diff_queue (int /*<<< orphan*/ *,struct diff_filespec*,struct diff_filespec*) ; 
 TYPE_3__* rename_dst ; 
 TYPE_2__* rename_src ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void record_rename_pair(int dst_index, int src_index, int score)
{
	struct diff_filespec *src, *dst;
	struct diff_filepair *dp;

	if (rename_dst[dst_index].pair)
		die("internal error: dst already matched.");

	src = rename_src[src_index].p->one;
	src->rename_used++;
	src->count++;

	dst = rename_dst[dst_index].two;
	dst->count++;

	dp = diff_queue(NULL, src, dst);
	dp->renamed_pair = 1;
	if (!strcmp(src->path, dst->path))
		dp->score = rename_src[src_index].score;
	else
		dp->score = score;
	rename_dst[dst_index].pair = dp;
}