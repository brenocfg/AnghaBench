#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct diffstat_t {int dummy; } ;
struct diff_options {TYPE_1__* repo; scalar_t__ prefix_length; } ;
struct diff_filepair {TYPE_2__* two; TYPE_2__* one; } ;
struct TYPE_6__ {char const* path; } ;
struct TYPE_5__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ DIFF_PAIR_UNMERGED (struct diff_filepair*) ; 
 int /*<<< orphan*/  builtin_diffstat (char const*,char const*,TYPE_2__*,TYPE_2__*,struct diffstat_t*,struct diff_options*,struct diff_filepair*) ; 
 int /*<<< orphan*/  diff_fill_oid_info (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strip_prefix (scalar_t__,char const**,char const**) ; 

__attribute__((used)) static void run_diffstat(struct diff_filepair *p, struct diff_options *o,
			 struct diffstat_t *diffstat)
{
	const char *name;
	const char *other;

	if (DIFF_PAIR_UNMERGED(p)) {
		/* unmerged */
		builtin_diffstat(p->one->path, NULL, NULL, NULL,
				 diffstat, o, p);
		return;
	}

	name = p->one->path;
	other = (strcmp(name, p->two->path) ? p->two->path : NULL);

	if (o->prefix_length)
		strip_prefix(o->prefix_length, &name, &other);

	diff_fill_oid_info(p->one, o->repo->index);
	diff_fill_oid_info(p->two, o->repo->index);

	builtin_diffstat(name, other, p->one, p->two,
			 diffstat, o, p);
}