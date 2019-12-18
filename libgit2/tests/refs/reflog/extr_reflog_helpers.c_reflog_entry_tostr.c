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
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_buf_printf (int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entry_id_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_entry_id_old (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_entry_message (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int reflog_entry_tostr(git_buf *out, const git_reflog_entry *entry)
{
	char old_oid[GIT_OID_HEXSZ], new_oid[GIT_OID_HEXSZ];

	assert(out && entry);

	git_oid_tostr((char *)&old_oid, GIT_OID_HEXSZ, git_reflog_entry_id_old(entry));
	git_oid_tostr((char *)&new_oid, GIT_OID_HEXSZ, git_reflog_entry_id_new(entry));

	return git_buf_printf(out, "%s %s %s %s", old_oid, new_oid, "somesig", git_reflog_entry_message(entry));
}