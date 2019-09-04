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
struct strbuf {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct notes_tree {int /*<<< orphan*/ * update_ref; int /*<<< orphan*/  dirty; int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UPDATE_REFS_DIE_ON_ERR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  create_notes_commit (struct repository*,struct notes_tree*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 
 struct notes_tree default_notes_tree ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_complete_line (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  update_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void commit_notes(struct repository *r, struct notes_tree *t, const char *msg)
{
	struct strbuf buf = STRBUF_INIT;
	struct object_id commit_oid;

	if (!t)
		t = &default_notes_tree;
	if (!t->initialized || !t->update_ref || !*t->update_ref)
		die(_("Cannot commit uninitialized/unreferenced notes tree"));
	if (!t->dirty)
		return; /* don't have to commit an unchanged tree */

	/* Prepare commit message and reflog message */
	strbuf_addstr(&buf, msg);
	strbuf_complete_line(&buf);

	create_notes_commit(r, t, NULL, buf.buf, buf.len, &commit_oid);
	strbuf_insert(&buf, 0, "notes: ", 7); /* commit message starts at index 7 */
	update_ref(buf.buf, t->update_ref, &commit_oid, NULL, 0,
		   UPDATE_REFS_DIE_ON_ERR);

	strbuf_release(&buf);
}