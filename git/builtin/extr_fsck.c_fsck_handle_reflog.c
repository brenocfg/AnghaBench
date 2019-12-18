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

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  for_each_reflog_ent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsck_handle_reflog_ent ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_worktree_ref (void*,struct strbuf*,char const*) ; 

__attribute__((used)) static int fsck_handle_reflog(const char *logname, const struct object_id *oid,
			      int flag, void *cb_data)
{
	struct strbuf refname = STRBUF_INIT;

	strbuf_worktree_ref(cb_data, &refname, logname);
	for_each_reflog_ent(refname.buf, fsck_handle_reflog_ent, refname.buf);
	strbuf_release(&refname);
	return 0;
}