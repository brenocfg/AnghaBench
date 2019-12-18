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
struct strbuf {char const* buf; } ;
struct lock_file {int dummy; } ;
struct TYPE_5__ {TYPE_1__* objects; } ;
struct TYPE_4__ {scalar_t__ loaded_alternates; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ commit_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen_lock_file (struct lock_file*,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf_or_die (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* git_pathdup (char*) ; 
 int /*<<< orphan*/  hold_lock_file_for_update (struct lock_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_alt_odb_entries (TYPE_2__*,char const*,char,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 TYPE_2__* the_repository ; 

void add_to_alternates_file(const char *reference)
{
	struct lock_file lock = LOCK_INIT;
	char *alts = git_pathdup("objects/info/alternates");
	FILE *in, *out;
	int found = 0;

	hold_lock_file_for_update(&lock, alts, LOCK_DIE_ON_ERROR);
	out = fdopen_lock_file(&lock, "w");
	if (!out)
		die_errno(_("unable to fdopen alternates lockfile"));

	in = fopen(alts, "r");
	if (in) {
		struct strbuf line = STRBUF_INIT;

		while (strbuf_getline(&line, in) != EOF) {
			if (!strcmp(reference, line.buf)) {
				found = 1;
				break;
			}
			fprintf_or_die(out, "%s\n", line.buf);
		}

		strbuf_release(&line);
		fclose(in);
	}
	else if (errno != ENOENT)
		die_errno(_("unable to read alternates file"));

	if (found) {
		rollback_lock_file(&lock);
	} else {
		fprintf_or_die(out, "%s\n", reference);
		if (commit_lock_file(&lock))
			die_errno(_("unable to move new alternates file into place"));
		if (the_repository->objects->loaded_alternates)
			link_alt_odb_entries(the_repository, reference,
					     '\n', NULL, 0);
	}
	free(alts);
}