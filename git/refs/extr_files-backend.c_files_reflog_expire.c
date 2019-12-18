#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; } ;
struct ref_store {int dummy; } ;
struct lock_file {int dummy; } ;
struct ref_lock {char* ref_name; struct lock_file lk; } ;
struct object_id {int dummy; } ;
struct files_ref_store {int dummy; } ;
struct expire_reflog_cb {unsigned int flags; int /*<<< orphan*/  last_kept_oid; void* policy_cb; int /*<<< orphan*/  newlog; int /*<<< orphan*/  should_prune_fn; } ;
typedef  int /*<<< orphan*/  reflog_expiry_should_prune_fn ;
typedef  int /*<<< orphan*/  (* reflog_expiry_prepare_fn ) (char const*,struct object_id const*,void*) ;
typedef  int /*<<< orphan*/  (* reflog_expiry_cleanup_fn ) (void*) ;
typedef  int /*<<< orphan*/  cb ;
struct TYPE_2__ {int /*<<< orphan*/  hexsz; } ;

/* Variables and functions */
 unsigned int EXPIRE_REFLOGS_DRY_RUN ; 
 unsigned int EXPIRE_REFLOGS_UPDATE_REF ; 
 struct lock_file LOCK_INIT ; 
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  REF_NO_DEREF ; 
 int /*<<< orphan*/  REF_STORE_WRITE ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ close_lock_file_gently (struct lock_file*) ; 
 scalar_t__ close_ref_gently (struct ref_lock*) ; 
 scalar_t__ commit_lock_file (struct lock_file*) ; 
 scalar_t__ commit_ref (struct ref_lock*) ; 
 int /*<<< orphan*/  errno ; 
 int error (char*,char const*,...) ; 
 int /*<<< orphan*/  expire_reflog_ent ; 
 int /*<<< orphan*/  fdopen_lock_file (struct lock_file*,char*) ; 
 struct files_ref_store* files_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  files_reflog_path (struct files_ref_store*,struct strbuf*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_lock_file_fd (struct lock_file*) ; 
 char* get_lock_file_path (struct lock_file*) ; 
 scalar_t__ hold_lock_file_for_update (struct lock_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 
 struct ref_lock* lock_ref_oid_basic (struct files_ref_store*,char const*,struct object_id const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,struct strbuf*) ; 
 int /*<<< orphan*/  memset (struct expire_reflog_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refs_for_each_reflog_ent (struct ref_store*,char const*,int /*<<< orphan*/ ,struct expire_reflog_cb*) ; 
 int /*<<< orphan*/  refs_reflog_exists (struct ref_store*,char const*) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char const*,struct object_id const*,void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  unable_to_lock_message (char*,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  unlock_ref (struct ref_lock*) ; 
 scalar_t__ write_in_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_str_in_full (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int files_reflog_expire(struct ref_store *ref_store,
			       const char *refname, const struct object_id *oid,
			       unsigned int flags,
			       reflog_expiry_prepare_fn prepare_fn,
			       reflog_expiry_should_prune_fn should_prune_fn,
			       reflog_expiry_cleanup_fn cleanup_fn,
			       void *policy_cb_data)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE, "reflog_expire");
	struct lock_file reflog_lock = LOCK_INIT;
	struct expire_reflog_cb cb;
	struct ref_lock *lock;
	struct strbuf log_file_sb = STRBUF_INIT;
	char *log_file;
	int status = 0;
	int type;
	struct strbuf err = STRBUF_INIT;

	memset(&cb, 0, sizeof(cb));
	cb.flags = flags;
	cb.policy_cb = policy_cb_data;
	cb.should_prune_fn = should_prune_fn;

	/*
	 * The reflog file is locked by holding the lock on the
	 * reference itself, plus we might need to update the
	 * reference if --updateref was specified:
	 */
	lock = lock_ref_oid_basic(refs, refname, oid,
				  NULL, NULL, REF_NO_DEREF,
				  &type, &err);
	if (!lock) {
		error("cannot lock ref '%s': %s", refname, err.buf);
		strbuf_release(&err);
		return -1;
	}
	if (!refs_reflog_exists(ref_store, refname)) {
		unlock_ref(lock);
		return 0;
	}

	files_reflog_path(refs, &log_file_sb, refname);
	log_file = strbuf_detach(&log_file_sb, NULL);
	if (!(flags & EXPIRE_REFLOGS_DRY_RUN)) {
		/*
		 * Even though holding $GIT_DIR/logs/$reflog.lock has
		 * no locking implications, we use the lock_file
		 * machinery here anyway because it does a lot of the
		 * work we need, including cleaning up if the program
		 * exits unexpectedly.
		 */
		if (hold_lock_file_for_update(&reflog_lock, log_file, 0) < 0) {
			struct strbuf err = STRBUF_INIT;
			unable_to_lock_message(log_file, errno, &err);
			error("%s", err.buf);
			strbuf_release(&err);
			goto failure;
		}
		cb.newlog = fdopen_lock_file(&reflog_lock, "w");
		if (!cb.newlog) {
			error("cannot fdopen %s (%s)",
			      get_lock_file_path(&reflog_lock), strerror(errno));
			goto failure;
		}
	}

	(*prepare_fn)(refname, oid, cb.policy_cb);
	refs_for_each_reflog_ent(ref_store, refname, expire_reflog_ent, &cb);
	(*cleanup_fn)(cb.policy_cb);

	if (!(flags & EXPIRE_REFLOGS_DRY_RUN)) {
		/*
		 * It doesn't make sense to adjust a reference pointed
		 * to by a symbolic ref based on expiring entries in
		 * the symbolic reference's reflog. Nor can we update
		 * a reference if there are no remaining reflog
		 * entries.
		 */
		int update = (flags & EXPIRE_REFLOGS_UPDATE_REF) &&
			!(type & REF_ISSYMREF) &&
			!is_null_oid(&cb.last_kept_oid);

		if (close_lock_file_gently(&reflog_lock)) {
			status |= error("couldn't write %s: %s", log_file,
					strerror(errno));
			rollback_lock_file(&reflog_lock);
		} else if (update &&
			   (write_in_full(get_lock_file_fd(&lock->lk),
				oid_to_hex(&cb.last_kept_oid), the_hash_algo->hexsz) < 0 ||
			    write_str_in_full(get_lock_file_fd(&lock->lk), "\n") < 0 ||
			    close_ref_gently(lock) < 0)) {
			status |= error("couldn't write %s",
					get_lock_file_path(&lock->lk));
			rollback_lock_file(&reflog_lock);
		} else if (commit_lock_file(&reflog_lock)) {
			status |= error("unable to write reflog '%s' (%s)",
					log_file, strerror(errno));
		} else if (update && commit_ref(lock)) {
			status |= error("couldn't set %s", lock->ref_name);
		}
	}
	free(log_file);
	unlock_ref(lock);
	return status;

 failure:
	rollback_lock_file(&reflog_lock);
	free(log_file);
	unlock_ref(lock);
	return -1;
}