#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* tempfile; } ;
struct ref_lock {TYPE_3__ lk; } ;
struct files_ref_store {int dummy; } ;
struct TYPE_4__ {char const* buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  fp; TYPE_1__ filename; } ;

/* Variables and functions */
 scalar_t__ commit_ref (struct ref_lock*) ; 
 int /*<<< orphan*/  create_ref_symlink (struct ref_lock*,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int error (char*,char const*,char*) ; 
 int /*<<< orphan*/  fdopen_lock_file (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ prefer_symlink_refs ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_symref_reflog (struct files_ref_store*,struct ref_lock*,char const*,char const*,char const*) ; 

__attribute__((used)) static int create_symref_locked(struct files_ref_store *refs,
				struct ref_lock *lock, const char *refname,
				const char *target, const char *logmsg)
{
	if (prefer_symlink_refs && !create_ref_symlink(lock, target)) {
		update_symref_reflog(refs, lock, refname, target, logmsg);
		return 0;
	}

	if (!fdopen_lock_file(&lock->lk, "w"))
		return error("unable to fdopen %s: %s",
			     lock->lk.tempfile->filename.buf, strerror(errno));

	update_symref_reflog(refs, lock, refname, target, logmsg);

	/* no error check; commit_ref will check ferror */
	fprintf(lock->lk.tempfile->fp, "ref: %s\n", target);
	if (commit_ref(lock) < 0)
		return error("unable to write symref for %s: %s", refname,
			     strerror(errno));
	return 0;
}