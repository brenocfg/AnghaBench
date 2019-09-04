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
struct oid_array {int dummy; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* git_path_fetch_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,struct object_id*) ; 
 scalar_t__ parse_oid_hex (int /*<<< orphan*/ ,struct object_id*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/ * xfopen (char const*,char*) ; 

__attribute__((used)) static void get_merge_heads(struct oid_array *merge_heads)
{
	const char *filename = git_path_fetch_head(the_repository);
	FILE *fp;
	struct strbuf sb = STRBUF_INIT;
	struct object_id oid;

	fp = xfopen(filename, "r");
	while (strbuf_getline_lf(&sb, fp) != EOF) {
		const char *p;
		if (parse_oid_hex(sb.buf, &oid, &p))
			continue;  /* invalid line: does not start with object ID */
		if (starts_with(p, "\tnot-for-merge\t"))
			continue;  /* ref is not-for-merge */
		oid_array_append(merge_heads, &oid);
	}
	fclose(fp);
	strbuf_release(&sb);
}