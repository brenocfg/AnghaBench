#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* path; } ;
typedef  TYPE_1__ git_diff_file ;
typedef  int git_checkout_notify_t ;
struct TYPE_8__ {scalar_t__ debug; int /*<<< orphan*/  n_ignored; int /*<<< orphan*/  n_untracked; int /*<<< orphan*/  n_updates; int /*<<< orphan*/  n_dirty; int /*<<< orphan*/  n_conflicts; } ;
typedef  TYPE_2__ checkout_counts ;

/* Variables and functions */
 int GIT_CHECKOUT_NOTIFY_CONFLICT ; 
 int GIT_CHECKOUT_NOTIFY_DIRTY ; 
 int GIT_CHECKOUT_NOTIFY_IGNORED ; 
 int GIT_CHECKOUT_NOTIFY_UNTRACKED ; 
 int GIT_CHECKOUT_NOTIFY_UPDATED ; 
 int /*<<< orphan*/  GIT_UNUSED (TYPE_1__ const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 

int checkout_count_callback(
	git_checkout_notify_t why,
	const char *path,
	const git_diff_file *baseline,
	const git_diff_file *target,
	const git_diff_file *workdir,
	void *payload)
{
	checkout_counts *ct = payload;

	GIT_UNUSED(baseline); GIT_UNUSED(target); GIT_UNUSED(workdir);

	if (why & GIT_CHECKOUT_NOTIFY_CONFLICT) {
		ct->n_conflicts++;

		if (ct->debug) {
			if (workdir) {
				if (baseline) {
					if (target)
						fprintf(stderr, "M %s (conflicts with M %s)\n",
							workdir->path, target->path);
					else
						fprintf(stderr, "M %s (conflicts with D %s)\n",
							workdir->path, baseline->path);
				} else {
					if (target)
						fprintf(stderr, "Existing %s (conflicts with A %s)\n",
							workdir->path, target->path);
					else
						fprintf(stderr, "How can an untracked file be a conflict (%s)\n", workdir->path);
				}
			} else {
				if (baseline) {
					if (target)
						fprintf(stderr, "D %s (conflicts with M %s)\n",
							target->path, baseline->path);
					else
						fprintf(stderr, "D %s (conflicts with D %s)\n",
							baseline->path, baseline->path);
				} else {
					if (target)
						fprintf(stderr, "How can an added file with no workdir be a conflict (%s)\n", target->path);
					else
						fprintf(stderr, "How can a nonexistent file be a conflict (%s)\n", path);
				}
			}
		}
	}

	if (why & GIT_CHECKOUT_NOTIFY_DIRTY) {
		ct->n_dirty++;

		if (ct->debug) {
			if (workdir)
				fprintf(stderr, "M %s\n", workdir->path);
			else
				fprintf(stderr, "D %s\n", baseline->path);
		}
	}

	if (why & GIT_CHECKOUT_NOTIFY_UPDATED) {
		ct->n_updates++;

		if (ct->debug) {
			if (baseline) {
				if (target)
					fprintf(stderr, "update: M %s\n", path);
				else
					fprintf(stderr, "update: D %s\n", path);
			} else {
				if (target)
					fprintf(stderr, "update: A %s\n", path);
				else
					fprintf(stderr, "update: this makes no sense %s\n", path);
			}
		}
	}

	if (why & GIT_CHECKOUT_NOTIFY_UNTRACKED) {
		ct->n_untracked++;

		if (ct->debug)
			fprintf(stderr, "? %s\n", path);
	}

	if (why & GIT_CHECKOUT_NOTIFY_IGNORED) {
		ct->n_ignored++;

		if (ct->debug)
			fprintf(stderr, "I %s\n", path);
	}

	return 0;
}