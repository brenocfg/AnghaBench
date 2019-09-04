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
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct dirstat_dir {int nr; TYPE_6__* files; scalar_t__ alloc; int /*<<< orphan*/  cumulative; int /*<<< orphan*/  permille; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct TYPE_9__ {scalar_t__ dirstat_by_file; int /*<<< orphan*/  dirstat_cumulative; } ;
struct diff_options {int /*<<< orphan*/  repo; TYPE_1__ flags; int /*<<< orphan*/  dirstat_permille; } ;
struct diff_filepair {TYPE_2__* one; TYPE_2__* two; } ;
struct TYPE_11__ {char const* name; unsigned long changed; } ;
struct TYPE_10__ {char* path; unsigned long size; int /*<<< orphan*/  oid; scalar_t__ oid_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_6__*,int,scalar_t__) ; 
 int /*<<< orphan*/  CHECK_SIZE_ONLY ; 
 scalar_t__ DIFF_FILE_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  QSORT (TYPE_6__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_free_filespec_data (TYPE_2__*) ; 
 int /*<<< orphan*/  diff_populate_filespec (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct diff_queue_struct diff_queued_diff ; 
 int /*<<< orphan*/  diffcore_count_changes (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  dirstat_compare ; 
 int /*<<< orphan*/  gather_dirstat (struct diff_options*,struct dirstat_dir*,unsigned long,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void show_dirstat(struct diff_options *options)
{
	int i;
	unsigned long changed;
	struct dirstat_dir dir;
	struct diff_queue_struct *q = &diff_queued_diff;

	dir.files = NULL;
	dir.alloc = 0;
	dir.nr = 0;
	dir.permille = options->dirstat_permille;
	dir.cumulative = options->flags.dirstat_cumulative;

	changed = 0;
	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		const char *name;
		unsigned long copied, added, damage;

		name = p->two->path ? p->two->path : p->one->path;

		if (p->one->oid_valid && p->two->oid_valid &&
		    oideq(&p->one->oid, &p->two->oid)) {
			/*
			 * The SHA1 has not changed, so pre-/post-content is
			 * identical. We can therefore skip looking at the
			 * file contents altogether.
			 */
			damage = 0;
			goto found_damage;
		}

		if (options->flags.dirstat_by_file) {
			/*
			 * In --dirstat-by-file mode, we don't really need to
			 * look at the actual file contents at all.
			 * The fact that the SHA1 changed is enough for us to
			 * add this file to the list of results
			 * (with each file contributing equal damage).
			 */
			damage = 1;
			goto found_damage;
		}

		if (DIFF_FILE_VALID(p->one) && DIFF_FILE_VALID(p->two)) {
			diff_populate_filespec(options->repo, p->one, 0);
			diff_populate_filespec(options->repo, p->two, 0);
			diffcore_count_changes(options->repo,
					       p->one, p->two, NULL, NULL,
					       &copied, &added);
			diff_free_filespec_data(p->one);
			diff_free_filespec_data(p->two);
		} else if (DIFF_FILE_VALID(p->one)) {
			diff_populate_filespec(options->repo, p->one, CHECK_SIZE_ONLY);
			copied = added = 0;
			diff_free_filespec_data(p->one);
		} else if (DIFF_FILE_VALID(p->two)) {
			diff_populate_filespec(options->repo, p->two, CHECK_SIZE_ONLY);
			copied = 0;
			added = p->two->size;
			diff_free_filespec_data(p->two);
		} else
			continue;

		/*
		 * Original minus copied is the removed material,
		 * added is the new material.  They are both damages
		 * made to the preimage.
		 * If the resulting damage is zero, we know that
		 * diffcore_count_changes() considers the two entries to
		 * be identical, but since the oid changed, we
		 * know that there must have been _some_ kind of change,
		 * so we force all entries to have damage > 0.
		 */
		damage = (p->one->size - copied) + added;
		if (!damage)
			damage = 1;

found_damage:
		ALLOC_GROW(dir.files, dir.nr + 1, dir.alloc);
		dir.files[dir.nr].name = name;
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