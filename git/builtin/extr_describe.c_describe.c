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

/* Variables and functions */
 scalar_t__ OBJ_BLOB ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  clear_commit_marks (struct commit*,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  describe_blob (struct object_id,struct strbuf*) ; 
 int /*<<< orphan*/  describe_commit (struct object_id*,struct strbuf*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 struct commit* lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id*,int) ; 
 scalar_t__ oid_object_info (int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void describe(const char *arg, int last_one)
{
	struct object_id oid;
	struct commit *cmit;
	struct strbuf sb = STRBUF_INIT;

	if (debug)
		fprintf(stderr, _("describe %s\n"), arg);

	if (get_oid(arg, &oid))
		die(_("Not a valid object name %s"), arg);
	cmit = lookup_commit_reference_gently(the_repository, &oid, 1);

	if (cmit)
		describe_commit(&oid, &sb);
	else if (oid_object_info(the_repository, &oid, NULL) == OBJ_BLOB)
		describe_blob(oid, &sb);
	else
		die(_("%s is neither a commit nor blob"), arg);

	puts(sb.buf);

	if (!last_one)
		clear_commit_marks(cmit, -1);

	strbuf_release(&sb);
}