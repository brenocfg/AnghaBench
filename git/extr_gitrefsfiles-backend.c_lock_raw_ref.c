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
struct string_list {int dummy; } ;
struct strbuf {char const* buf; } ;
struct ref_lock {int /*<<< orphan*/  old_oid; int /*<<< orphan*/  lk; int /*<<< orphan*/  ref_name; } ;
struct files_ref_store {int /*<<< orphan*/ * packed_ref_store; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ EISDIR ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOCK_NO_DEREF ; 
 unsigned int REF_ISBROKEN ; 
 int /*<<< orphan*/  REMOVE_DIR_EMPTY_ONLY ; 
#define  SCLD_EXISTS 130 
#define  SCLD_OK 129 
#define  SCLD_VANISHED 128 
 struct strbuf STRBUF_INIT ; 
 int TRANSACTION_GENERIC_ERROR ; 
 int TRANSACTION_NAME_CONFLICT ; 
 int /*<<< orphan*/  assert (struct strbuf*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  files_assert_main_repository (struct files_ref_store*,char*) ; 
 scalar_t__ files_read_raw_ref (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,struct strbuf*,unsigned int*) ; 
 int /*<<< orphan*/  files_ref_path (struct files_ref_store*,struct strbuf*,char const*) ; 
 int /*<<< orphan*/  get_files_ref_lock_timeout_ms () ; 
 scalar_t__ hold_lock_file_for_update_timeout (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ refs_verify_refname_available (int /*<<< orphan*/ *,char const*,struct string_list const*,struct string_list const*,struct strbuf*) ; 
 scalar_t__ remove_dir_recursively (struct strbuf*,int /*<<< orphan*/ ) ; 
 int safe_create_leading_directories (char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 char const* strerror (scalar_t__) ; 
 int /*<<< orphan*/  unable_to_lock_message (char const*,scalar_t__,struct strbuf*) ; 
 int /*<<< orphan*/  unlock_ref (struct ref_lock*) ; 
 struct ref_lock* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int lock_raw_ref(struct files_ref_store *refs,
			const char *refname, int mustexist,
			const struct string_list *extras,
			const struct string_list *skip,
			struct ref_lock **lock_p,
			struct strbuf *referent,
			unsigned int *type,
			struct strbuf *err)
{
	struct ref_lock *lock;
	struct strbuf ref_file = STRBUF_INIT;
	int attempts_remaining = 3;
	int ret = TRANSACTION_GENERIC_ERROR;

	assert(err);
	files_assert_main_repository(refs, "lock_raw_ref");

	*type = 0;

	/* First lock the file so it can't change out from under us. */

	*lock_p = lock = xcalloc(1, sizeof(*lock));

	lock->ref_name = xstrdup(refname);
	files_ref_path(refs, &ref_file, refname);

retry:
	switch (safe_create_leading_directories(ref_file.buf)) {
	case SCLD_OK:
		break; /* success */
	case SCLD_EXISTS:
		/*
		 * Suppose refname is "refs/foo/bar". We just failed
		 * to create the containing directory, "refs/foo",
		 * because there was a non-directory in the way. This
		 * indicates a D/F conflict, probably because of
		 * another reference such as "refs/foo". There is no
		 * reason to expect this error to be transitory.
		 */
		if (refs_verify_refname_available(&refs->base, refname,
						  extras, skip, err)) {
			if (mustexist) {
				/*
				 * To the user the relevant error is
				 * that the "mustexist" reference is
				 * missing:
				 */
				strbuf_reset(err);
				strbuf_addf(err, "unable to resolve reference '%s'",
					    refname);
			} else {
				/*
				 * The error message set by
				 * refs_verify_refname_available() is
				 * OK.
				 */
				ret = TRANSACTION_NAME_CONFLICT;
			}
		} else {
			/*
			 * The file that is in the way isn't a loose
			 * reference. Report it as a low-level
			 * failure.
			 */
			strbuf_addf(err, "unable to create lock file %s.lock; "
				    "non-directory in the way",
				    ref_file.buf);
		}
		goto error_return;
	case SCLD_VANISHED:
		/* Maybe another process was tidying up. Try again. */
		if (--attempts_remaining > 0)
			goto retry;
		/* fall through */
	default:
		strbuf_addf(err, "unable to create directory for %s",
			    ref_file.buf);
		goto error_return;
	}

	if (hold_lock_file_for_update_timeout(
			    &lock->lk, ref_file.buf, LOCK_NO_DEREF,
			    get_files_ref_lock_timeout_ms()) < 0) {
		if (errno == ENOENT && --attempts_remaining > 0) {
			/*
			 * Maybe somebody just deleted one of the
			 * directories leading to ref_file.  Try
			 * again:
			 */
			goto retry;
		} else {
			unable_to_lock_message(ref_file.buf, errno, err);
			goto error_return;
		}
	}

	/*
	 * Now we hold the lock and can read the reference without
	 * fear that its value will change.
	 */

	if (files_read_raw_ref(&refs->base, refname,
			       &lock->old_oid, referent, type)) {
		if (errno == ENOENT) {
			if (mustexist) {
				/* Garden variety missing reference. */
				strbuf_addf(err, "unable to resolve reference '%s'",
					    refname);
				goto error_return;
			} else {
				/*
				 * Reference is missing, but that's OK. We
				 * know that there is not a conflict with
				 * another loose reference because
				 * (supposing that we are trying to lock
				 * reference "refs/foo/bar"):
				 *
				 * - We were successfully able to create
				 *   the lockfile refs/foo/bar.lock, so we
				 *   know there cannot be a loose reference
				 *   named "refs/foo".
				 *
				 * - We got ENOENT and not EISDIR, so we
				 *   know that there cannot be a loose
				 *   reference named "refs/foo/bar/baz".
				 */
			}
		} else if (errno == EISDIR) {
			/*
			 * There is a directory in the way. It might have
			 * contained references that have been deleted. If
			 * we don't require that the reference already
			 * exists, try to remove the directory so that it
			 * doesn't cause trouble when we want to rename the
			 * lockfile into place later.
			 */
			if (mustexist) {
				/* Garden variety missing reference. */
				strbuf_addf(err, "unable to resolve reference '%s'",
					    refname);
				goto error_return;
			} else if (remove_dir_recursively(&ref_file,
							  REMOVE_DIR_EMPTY_ONLY)) {
				if (refs_verify_refname_available(
						    &refs->base, refname,
						    extras, skip, err)) {
					/*
					 * The error message set by
					 * verify_refname_available() is OK.
					 */
					ret = TRANSACTION_NAME_CONFLICT;
					goto error_return;
				} else {
					/*
					 * We can't delete the directory,
					 * but we also don't know of any
					 * references that it should
					 * contain.
					 */
					strbuf_addf(err, "there is a non-empty directory '%s' "
						    "blocking reference '%s'",
						    ref_file.buf, refname);
					goto error_return;
				}
			}
		} else if (errno == EINVAL && (*type & REF_ISBROKEN)) {
			strbuf_addf(err, "unable to resolve reference '%s': "
				    "reference broken", refname);
			goto error_return;
		} else {
			strbuf_addf(err, "unable to resolve reference '%s': %s",
				    refname, strerror(errno));
			goto error_return;
		}

		/*
		 * If the ref did not exist and we are creating it,
		 * make sure there is no existing packed ref that
		 * conflicts with refname:
		 */
		if (refs_verify_refname_available(
				    refs->packed_ref_store, refname,
				    extras, skip, err))
			goto error_return;
	}

	ret = 0;
	goto out;

error_return:
	unlock_ref(lock);
	*lock_p = NULL;

out:
	strbuf_release(&ref_file);
	return ret;
}