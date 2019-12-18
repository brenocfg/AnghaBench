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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct commit_list {int dummy; } ;
struct commit_extra_header {struct commit_extra_header* next; } ;
struct TYPE_2__ {struct object_id const oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDENT_STRICT ; 
 int /*<<< orphan*/  OBJ_TREE ; 
 char* _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_extra_header (struct strbuf*,struct commit_extra_header*) ; 
 int /*<<< orphan*/  assert_oid_type (struct object_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_type ; 
 int /*<<< orphan*/  commit_utf8_warn ; 
 scalar_t__ do_sign_commit (struct strbuf*,char const*) ; 
 int error (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* git_author_info (int /*<<< orphan*/ ) ; 
 char const* git_commit_encoding ; 
 char const* git_committer_info (int /*<<< orphan*/ ) ; 
 int is_encoding_utf8 (char const*) ; 
 scalar_t__ memchr (char const*,char,size_t) ; 
 char const* oid_to_hex (struct object_id const*) ; 
 struct commit* pop_commit (struct commit_list**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  verify_utf8 (struct strbuf*) ; 
 int write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 

int commit_tree_extended(const char *msg, size_t msg_len,
			 const struct object_id *tree,
			 struct commit_list *parents, struct object_id *ret,
			 const char *author, const char *sign_commit,
			 struct commit_extra_header *extra)
{
	int result;
	int encoding_is_utf8;
	struct strbuf buffer;

	assert_oid_type(tree, OBJ_TREE);

	if (memchr(msg, '\0', msg_len))
		return error("a NUL byte in commit log message not allowed.");

	/* Not having i18n.commitencoding is the same as having utf-8 */
	encoding_is_utf8 = is_encoding_utf8(git_commit_encoding);

	strbuf_init(&buffer, 8192); /* should avoid reallocs for the headers */
	strbuf_addf(&buffer, "tree %s\n", oid_to_hex(tree));

	/*
	 * NOTE! This ordering means that the same exact tree merged with a
	 * different order of parents will be a _different_ changeset even
	 * if everything else stays the same.
	 */
	while (parents) {
		struct commit *parent = pop_commit(&parents);
		strbuf_addf(&buffer, "parent %s\n",
			    oid_to_hex(&parent->object.oid));
	}

	/* Person/date information */
	if (!author)
		author = git_author_info(IDENT_STRICT);
	strbuf_addf(&buffer, "author %s\n", author);
	strbuf_addf(&buffer, "committer %s\n", git_committer_info(IDENT_STRICT));
	if (!encoding_is_utf8)
		strbuf_addf(&buffer, "encoding %s\n", git_commit_encoding);

	while (extra) {
		add_extra_header(&buffer, extra);
		extra = extra->next;
	}
	strbuf_addch(&buffer, '\n');

	/* And add the comment */
	strbuf_add(&buffer, msg, msg_len);

	/* And check the encoding */
	if (encoding_is_utf8 && !verify_utf8(&buffer))
		fprintf(stderr, _(commit_utf8_warn));

	if (sign_commit && do_sign_commit(&buffer, sign_commit)) {
		result = -1;
		goto out;
	}

	result = write_object_file(buffer.buf, buffer.len, commit_type, ret);
out:
	strbuf_release(&buffer);
	return result;
}