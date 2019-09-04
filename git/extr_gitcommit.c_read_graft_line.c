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
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;
struct object_id {int dummy; } ;
struct commit_graft {int nr_parent; struct object_id* parent; struct object_id oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  isspace (int /*<<< orphan*/ ) ; 
 scalar_t__ parse_oid_hex (char const*,struct object_id*,char const**) ; 
 int /*<<< orphan*/  st_add (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_mult (int,int) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 struct commit_graft* xmalloc (int /*<<< orphan*/ ) ; 

struct commit_graft *read_graft_line(struct strbuf *line)
{
	/* The format is just "Commit Parent1 Parent2 ...\n" */
	int i, phase;
	const char *tail = NULL;
	struct commit_graft *graft = NULL;
	struct object_id dummy_oid, *oid;

	strbuf_rtrim(line);
	if (!line->len || line->buf[0] == '#')
		return NULL;
	/*
	 * phase 0 verifies line, counts hashes in line and allocates graft
	 * phase 1 fills graft
	 */
	for (phase = 0; phase < 2; phase++) {
		oid = graft ? &graft->oid : &dummy_oid;
		if (parse_oid_hex(line->buf, oid, &tail))
			goto bad_graft_data;
		for (i = 0; *tail != '\0'; i++) {
			oid = graft ? &graft->parent[i] : &dummy_oid;
			if (!isspace(*tail++) || parse_oid_hex(tail, oid, &tail))
				goto bad_graft_data;
		}
		if (!graft) {
			graft = xmalloc(st_add(sizeof(*graft),
					       st_mult(sizeof(struct object_id), i)));
			graft->nr_parent = i;
		}
	}
	return graft;

bad_graft_data:
	error("bad graft data: %s", line->buf);
	assert(!graft);
	return NULL;
}