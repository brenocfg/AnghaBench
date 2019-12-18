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
struct dirstat_dir {int nr; TYPE_2__* files; scalar_t__ alloc; int /*<<< orphan*/  cumulative; int /*<<< orphan*/  permille; } ;
struct diffstat_t {int nr; struct diffstat_file** files; } ;
struct diffstat_file {unsigned long added; unsigned long deleted; int /*<<< orphan*/  name; scalar_t__ is_binary; } ;
struct TYPE_4__ {int /*<<< orphan*/  dirstat_cumulative; } ;
struct diff_options {TYPE_1__ flags; int /*<<< orphan*/  dirstat_permille; } ;
struct TYPE_5__ {unsigned long changed; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_2__*,int,scalar_t__) ; 
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 int /*<<< orphan*/  QSORT (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirstat_compare ; 
 int /*<<< orphan*/  gather_dirstat (struct diff_options*,struct dirstat_dir*,unsigned long,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_dirstat_by_line(struct diffstat_t *data, struct diff_options *options)
{
	int i;
	unsigned long changed;
	struct dirstat_dir dir;

	if (data->nr == 0)
		return;

	dir.files = NULL;
	dir.alloc = 0;
	dir.nr = 0;
	dir.permille = options->dirstat_permille;
	dir.cumulative = options->flags.dirstat_cumulative;

	changed = 0;
	for (i = 0; i < data->nr; i++) {
		struct diffstat_file *file = data->files[i];
		unsigned long damage = file->added + file->deleted;
		if (file->is_binary)
			/*
			 * binary files counts bytes, not lines. Must find some
			 * way to normalize binary bytes vs. textual lines.
			 * The following heuristic assumes that there are 64
			 * bytes per "line".
			 * This is stupid and ugly, but very cheap...
			 */
			damage = DIV_ROUND_UP(damage, 64);
		ALLOC_GROW(dir.files, dir.nr + 1, dir.alloc);
		dir.files[dir.nr].name = file->name;
		dir.files[dir.nr].changed = damage;
		changed += damage;
		dir.nr++;
	}

	/* This can happen even with many files, if everything was renames */
	if (!changed)
		return;

	/* Show all directories with more than x% of the changes */
	QSORT(dir.files, dir.nr, dirstat_compare);
	gather_dirstat(options, &dir, changed, "", 0);
}