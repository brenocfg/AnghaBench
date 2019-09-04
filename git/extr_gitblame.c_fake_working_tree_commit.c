#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct stat {int st_mode; int /*<<< orphan*/  st_size; } ;
struct repository {TYPE_7__* index; } ;
struct object_id {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  allow_textconv; } ;
struct diff_options {TYPE_4__ flags; } ;
struct commit_list {TYPE_3__* item; struct commit_list* next; } ;
struct TYPE_13__ {int parsed; } ;
struct commit {struct commit_list* parents; int /*<<< orphan*/  date; TYPE_1__ object; } ;
struct cache_entry {int ce_namelen; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  name; int /*<<< orphan*/  oid; } ;
struct TYPE_17__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
struct blame_origin {int /*<<< orphan*/  blob_oid; TYPE_5__ file; } ;
struct TYPE_19__ {TYPE_6__** cache; } ;
struct TYPE_18__ {unsigned int ce_mode; } ;
struct TYPE_14__ {int /*<<< orphan*/  oid; } ;
struct TYPE_15__ {TYPE_2__ object; } ;

/* Variables and functions */
 int ADD_CACHE_OK_TO_ADD ; 
 int ADD_CACHE_OK_TO_REPLACE ; 
 int /*<<< orphan*/  OBJ_BLOB ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 struct strbuf STRBUF_INIT ; 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  WANT_BLANK_IDENT ; 
 int /*<<< orphan*/  add_index_entry (TYPE_7__*,struct cache_entry*,int) ; 
 struct commit* alloc_commit_node (struct repository*) ; 
 int /*<<< orphan*/  append_merge_parents (struct repository*,struct commit_list**) ; 
 struct commit_list** append_parent (struct repository*,struct commit_list**,struct object_id*) ; 
 int /*<<< orphan*/  cache_tree_invalidate_path (TYPE_7__*,char const*) ; 
 unsigned int canon_mode (int) ; 
 int /*<<< orphan*/  convert_to_git (TYPE_7__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ce_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ce_mode (unsigned int) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  die_errno (char*,...) ; 
 int /*<<< orphan*/  discard_index (TYPE_7__*) ; 
 char* fmt_ident (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int index_name_pos (TYPE_7__*,char const*,int) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 struct cache_entry* make_empty_cache_entry (TYPE_7__*,int) ; 
 struct blame_origin* make_origin (struct commit*,char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pretend_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo_read_index (struct repository*) ; 
 int /*<<< orphan*/  resolve_ref_unsafe (char*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_commit_buffer_from_strbuf (struct repository*,struct commit*,struct strbuf*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,char*,unsigned long,unsigned long) ; 
 scalar_t__ strbuf_read (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_read_file (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_readlink (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  textconv_object (struct repository*,char const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,unsigned long*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_working_tree_path (struct repository*,struct commit*,char const*) ; 

__attribute__((used)) static struct commit *fake_working_tree_commit(struct repository *r,
					       struct diff_options *opt,
					       const char *path,
					       const char *contents_from)
{
	struct commit *commit;
	struct blame_origin *origin;
	struct commit_list **parent_tail, *parent;
	struct object_id head_oid;
	struct strbuf buf = STRBUF_INIT;
	const char *ident;
	time_t now;
	int len;
	struct cache_entry *ce;
	unsigned mode;
	struct strbuf msg = STRBUF_INIT;

	repo_read_index(r);
	time(&now);
	commit = alloc_commit_node(r);
	commit->object.parsed = 1;
	commit->date = now;
	parent_tail = &commit->parents;

	if (!resolve_ref_unsafe("HEAD", RESOLVE_REF_READING, &head_oid, NULL))
		die("no such ref: HEAD");

	parent_tail = append_parent(r, parent_tail, &head_oid);
	append_merge_parents(r, parent_tail);
	verify_working_tree_path(r, commit, path);

	origin = make_origin(commit, path);

	ident = fmt_ident("Not Committed Yet", "not.committed.yet",
			WANT_BLANK_IDENT, NULL, 0);
	strbuf_addstr(&msg, "tree 0000000000000000000000000000000000000000\n");
	for (parent = commit->parents; parent; parent = parent->next)
		strbuf_addf(&msg, "parent %s\n",
			    oid_to_hex(&parent->item->object.oid));
	strbuf_addf(&msg,
		    "author %s\n"
		    "committer %s\n\n"
		    "Version of %s from %s\n",
		    ident, ident, path,
		    (!contents_from ? path :
		     (!strcmp(contents_from, "-") ? "standard input" : contents_from)));
	set_commit_buffer_from_strbuf(r, commit, &msg);

	if (!contents_from || strcmp("-", contents_from)) {
		struct stat st;
		const char *read_from;
		char *buf_ptr;
		unsigned long buf_len;

		if (contents_from) {
			if (stat(contents_from, &st) < 0)
				die_errno("Cannot stat '%s'", contents_from);
			read_from = contents_from;
		}
		else {
			if (lstat(path, &st) < 0)
				die_errno("Cannot lstat '%s'", path);
			read_from = path;
		}
		mode = canon_mode(st.st_mode);

		switch (st.st_mode & S_IFMT) {
		case S_IFREG:
			if (opt->flags.allow_textconv &&
			    textconv_object(r, read_from, mode, &null_oid, 0, &buf_ptr, &buf_len))
				strbuf_attach(&buf, buf_ptr, buf_len, buf_len + 1);
			else if (strbuf_read_file(&buf, read_from, st.st_size) != st.st_size)
				die_errno("cannot open or read '%s'", read_from);
			break;
		case S_IFLNK:
			if (strbuf_readlink(&buf, read_from, st.st_size) < 0)
				die_errno("cannot readlink '%s'", read_from);
			break;
		default:
			die("unsupported file type %s", read_from);
		}
	}
	else {
		/* Reading from stdin */
		mode = 0;
		if (strbuf_read(&buf, 0, 0) < 0)
			die_errno("failed to read from stdin");
	}
	convert_to_git(r->index, path, buf.buf, buf.len, &buf, 0);
	origin->file.ptr = buf.buf;
	origin->file.size = buf.len;
	pretend_object_file(buf.buf, buf.len, OBJ_BLOB, &origin->blob_oid);

	/*
	 * Read the current index, replace the path entry with
	 * origin->blob_sha1 without mucking with its mode or type
	 * bits; we are not going to write this index out -- we just
	 * want to run "diff-index --cached".
	 */
	discard_index(r->index);
	repo_read_index(r);

	len = strlen(path);
	if (!mode) {
		int pos = index_name_pos(r->index, path, len);
		if (0 <= pos)
			mode = r->index->cache[pos]->ce_mode;
		else
			/* Let's not bother reading from HEAD tree */
			mode = S_IFREG | 0644;
	}
	ce = make_empty_cache_entry(r->index, len);
	oidcpy(&ce->oid, &origin->blob_oid);
	memcpy(ce->name, path, len);
	ce->ce_flags = create_ce_flags(0);
	ce->ce_namelen = len;
	ce->ce_mode = create_ce_mode(mode);
	add_index_entry(r->index, ce,
			ADD_CACHE_OK_TO_ADD | ADD_CACHE_OK_TO_REPLACE);

	cache_tree_invalidate_path(r->index, path);

	return commit;
}