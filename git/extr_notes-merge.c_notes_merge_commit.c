#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; int len; } ;
struct stat {int dummy; } ;
struct object_id {int dummy; } ;
struct notes_tree {int dummy; } ;
struct notes_merge_options {int verbosity; TYPE_1__* repo; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
struct commit {int /*<<< orphan*/  parents; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_WRITE_OBJECT ; 
 int /*<<< orphan*/  NOTES_MERGE_WORKTREE ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ add_note (struct notes_tree*,struct object_id*,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_notes_commit (TYPE_1__*,struct notes_tree*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  die_errno (char*,char*) ; 
 char* get_commit_buffer (struct commit*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_oid_hex (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  git_path_buf (struct strbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ index_path (int /*<<< orphan*/ ,struct object_id*,char*,struct stat*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (char const*,char*) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit*,char const*) ; 

int notes_merge_commit(struct notes_merge_options *o,
		       struct notes_tree *partial_tree,
		       struct commit *partial_commit,
		       struct object_id *result_oid)
{
	/*
	 * Iterate through files in .git/NOTES_MERGE_WORKTREE and add all
	 * found notes to 'partial_tree'. Write the updated notes tree to
	 * the DB, and commit the resulting tree object while reusing the
	 * commit message and parents from 'partial_commit'.
	 * Finally store the new commit object OID into 'result_oid'.
	 */
	DIR *dir;
	struct dirent *e;
	struct strbuf path = STRBUF_INIT;
	const char *buffer = get_commit_buffer(partial_commit, NULL);
	const char *msg = strstr(buffer, "\n\n");
	int baselen;

	git_path_buf(&path, NOTES_MERGE_WORKTREE);
	if (o->verbosity >= 3)
		printf("Committing notes in notes merge worktree at %s\n",
			path.buf);

	if (!msg || msg[2] == '\0')
		die("partial notes commit has empty message");
	msg += 2;

	dir = opendir(path.buf);
	if (!dir)
		die_errno("could not open %s", path.buf);

	strbuf_addch(&path, '/');
	baselen = path.len;
	while ((e = readdir(dir)) != NULL) {
		struct stat st;
		struct object_id obj_oid, blob_oid;

		if (is_dot_or_dotdot(e->d_name))
			continue;

		if (get_oid_hex(e->d_name, &obj_oid)) {
			if (o->verbosity >= 3)
				printf("Skipping non-SHA1 entry '%s%s'\n",
					path.buf, e->d_name);
			continue;
		}

		strbuf_addstr(&path, e->d_name);
		/* write file as blob, and add to partial_tree */
		if (stat(path.buf, &st))
			die_errno("Failed to stat '%s'", path.buf);
		if (index_path(o->repo->index, &blob_oid, path.buf, &st, HASH_WRITE_OBJECT))
			die("Failed to write blob object from '%s'", path.buf);
		if (add_note(partial_tree, &obj_oid, &blob_oid, NULL))
			die("Failed to add resolved note '%s' to notes tree",
			    path.buf);
		if (o->verbosity >= 4)
			printf("Added resolved note for object %s: %s\n",
				oid_to_hex(&obj_oid), oid_to_hex(&blob_oid));
		strbuf_setlen(&path, baselen);
	}

	create_notes_commit(o->repo, partial_tree, partial_commit->parents, msg,
			    strlen(msg), result_oid);
	unuse_commit_buffer(partial_commit, buffer);
	if (o->verbosity >= 4)
		printf("Finalized notes merge commit: %s\n",
			oid_to_hex(result_oid));
	strbuf_release(&path);
	closedir(dir);
	return 0;
}