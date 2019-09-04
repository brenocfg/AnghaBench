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
struct ref_store {int dummy; } ;
struct ref_lock {int dummy; } ;
struct files_ref_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_NO_DEREF ; 
 int /*<<< orphan*/  REF_STORE_WRITE ; 
 struct strbuf STRBUF_INIT ; 
 int create_symref_locked (struct files_ref_store*,struct ref_lock*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 struct files_ref_store* files_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 struct ref_lock* lock_ref_oid_basic (struct files_ref_store*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  unlock_ref (struct ref_lock*) ; 

__attribute__((used)) static int files_create_symref(struct ref_store *ref_store,
			       const char *refname, const char *target,
			       const char *logmsg)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE, "create_symref");
	struct strbuf err = STRBUF_INIT;
	struct ref_lock *lock;
	int ret;

	lock = lock_ref_oid_basic(refs, refname, NULL,
				  NULL, NULL, REF_NO_DEREF, NULL,
				  &err);
	if (!lock) {
		error("%s", err.buf);
		strbuf_release(&err);
		return -1;
	}

	ret = create_symref_locked(refs, lock, refname, target, logmsg);
	unlock_ref(lock);
	return ret;
}