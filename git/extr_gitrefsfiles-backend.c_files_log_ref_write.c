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
struct files_ref_store {int dummy; } ;

/* Variables and functions */
 scalar_t__ LOG_REFS_NONE ; 
 scalar_t__ LOG_REFS_NORMAL ; 
 scalar_t__ LOG_REFS_UNSET ; 
 int REF_FORCE_CREATE_REFLOG ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ close (int) ; 
 int errno ; 
 int /*<<< orphan*/  files_reflog_path (struct files_ref_store*,struct strbuf*,char const*) ; 
 int /*<<< orphan*/  git_committer_info (int /*<<< orphan*/ ) ; 
 scalar_t__ is_bare_repository () ; 
 scalar_t__ log_all_ref_updates ; 
 int log_ref_setup (struct files_ref_store*,char const*,int,int*,struct strbuf*) ; 
 int log_ref_write_fd (int,struct object_id const*,struct object_id const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int files_log_ref_write(struct files_ref_store *refs,
			       const char *refname, const struct object_id *old_oid,
			       const struct object_id *new_oid, const char *msg,
			       int flags, struct strbuf *err)
{
	int logfd, result;

	if (log_all_ref_updates == LOG_REFS_UNSET)
		log_all_ref_updates = is_bare_repository() ? LOG_REFS_NONE : LOG_REFS_NORMAL;

	result = log_ref_setup(refs, refname,
			       flags & REF_FORCE_CREATE_REFLOG,
			       &logfd, err);

	if (result)
		return result;

	if (logfd < 0)
		return 0;
	result = log_ref_write_fd(logfd, old_oid, new_oid,
				  git_committer_info(0), msg);
	if (result) {
		struct strbuf sb = STRBUF_INIT;
		int save_errno = errno;

		files_reflog_path(refs, &sb, refname);
		strbuf_addf(err, "unable to append to '%s': %s",
			    sb.buf, strerror(save_errno));
		strbuf_release(&sb);
		close(logfd);
		return -1;
	}
	if (close(logfd)) {
		struct strbuf sb = STRBUF_INIT;
		int save_errno = errno;

		files_reflog_path(refs, &sb, refname);
		strbuf_addf(err, "unable to append to '%s': %s",
			    sb.buf, strerror(save_errno));
		strbuf_release(&sb);
		return -1;
	}
	return 0;
}