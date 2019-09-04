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
struct strbuf {int /*<<< orphan*/  len; } ;
struct object_id {int dummy; } ;
struct commit {int /*<<< orphan*/  date; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  DATE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
#define  OBJ_BLOB 131 
#define  OBJ_COMMIT 130 
#define  OBJ_TAG 129 
#define  OBJ_TREE 128 
 int /*<<< orphan*/  SHORT ; 
 int find_commit_subject (char*,char const**) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id const*) ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  show_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_add_unique_abbrev (struct strbuf*,struct object_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void create_reflog_msg(const struct object_id *oid, struct strbuf *sb)
{
	enum object_type type;
	struct commit *c;
	char *buf;
	unsigned long size;
	int subject_len = 0;
	const char *subject_start;

	char *rla = getenv("GIT_REFLOG_ACTION");
	if (rla) {
		strbuf_addstr(sb, rla);
	} else {
		strbuf_addstr(sb, "tag: tagging ");
		strbuf_add_unique_abbrev(sb, oid, DEFAULT_ABBREV);
	}

	strbuf_addstr(sb, " (");
	type = oid_object_info(the_repository, oid, NULL);
	switch (type) {
	default:
		strbuf_addstr(sb, "object of unknown type");
		break;
	case OBJ_COMMIT:
		if ((buf = read_object_file(oid, &type, &size)) != NULL) {
			subject_len = find_commit_subject(buf, &subject_start);
			strbuf_insert(sb, sb->len, subject_start, subject_len);
		} else {
			strbuf_addstr(sb, "commit object");
		}
		free(buf);

		if ((c = lookup_commit_reference(the_repository, oid)) != NULL)
			strbuf_addf(sb, ", %s", show_date(c->date, 0, DATE_MODE(SHORT)));
		break;
	case OBJ_TREE:
		strbuf_addstr(sb, "tree object");
		break;
	case OBJ_BLOB:
		strbuf_addstr(sb, "blob object");
		break;
	case OBJ_TAG:
		strbuf_addstr(sb, "other tag object");
		break;
	}
	strbuf_addch(sb, ')');
}