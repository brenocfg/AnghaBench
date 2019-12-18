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
struct ref_lock {int /*<<< orphan*/  old_oid; } ;
struct object_id {int dummy; } ;
struct files_ref_store {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ files_log_ref_write (struct files_ref_store*,char const*,int /*<<< orphan*/ *,struct object_id*,char const*,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  refs_read_ref_full (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void update_symref_reflog(struct files_ref_store *refs,
				 struct ref_lock *lock, const char *refname,
				 const char *target, const char *logmsg)
{
	struct strbuf err = STRBUF_INIT;
	struct object_id new_oid;
	if (logmsg &&
	    !refs_read_ref_full(&refs->base, target,
				RESOLVE_REF_READING, &new_oid, NULL) &&
	    files_log_ref_write(refs, refname, &lock->old_oid,
				&new_oid, logmsg, 0, &err)) {
		error("%s", err.buf);
		strbuf_release(&err);
	}
}