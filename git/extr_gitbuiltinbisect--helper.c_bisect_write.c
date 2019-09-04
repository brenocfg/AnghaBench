#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct commit {int dummy; } ;
struct bisect_terms {int /*<<< orphan*/  term_good; int /*<<< orphan*/  term_bad; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UPDATE_REFS_MSG_ON_ERR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int error_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  git_path_bisect_log () ; 
 int /*<<< orphan*/  log_commit (int /*<<< orphan*/ *,char*,char const*,struct commit*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id*) ; 
 scalar_t__ one_of (char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ update_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bisect_write(const char *state, const char *rev,
			const struct bisect_terms *terms, int nolog)
{
	struct strbuf tag = STRBUF_INIT;
	struct object_id oid;
	struct commit *commit;
	FILE *fp = NULL;
	int retval = 0;

	if (!strcmp(state, terms->term_bad)) {
		strbuf_addf(&tag, "refs/bisect/%s", state);
	} else if (one_of(state, terms->term_good, "skip", NULL)) {
		strbuf_addf(&tag, "refs/bisect/%s-%s", state, rev);
	} else {
		retval = error(_("Bad bisect_write argument: %s"), state);
		goto finish;
	}

	if (get_oid(rev, &oid)) {
		retval = error(_("couldn't get the oid of the rev '%s'"), rev);
		goto finish;
	}

	if (update_ref(NULL, tag.buf, &oid, NULL, 0,
		       UPDATE_REFS_MSG_ON_ERR)) {
		retval = -1;
		goto finish;
	}

	fp = fopen(git_path_bisect_log(), "a");
	if (!fp) {
		retval = error_errno(_("couldn't open the file '%s'"), git_path_bisect_log());
		goto finish;
	}

	commit = lookup_commit_reference(the_repository, &oid);
	log_commit(fp, "%s", state, commit);

	if (!nolog)
		fprintf(fp, "git bisect %s %s\n", state, rev);

finish:
	if (fp)
		fclose(fp);
	strbuf_release(&tag);
	return retval;
}