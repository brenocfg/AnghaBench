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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct lock_file {int dummy; } ;

/* Variables and functions */
 struct lock_file LOCK_INIT ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  commit_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  get_files_ref_lock_timeout_ms () ; 
 char* git_path (char*,char const*) ; 
 int hold_lock_file_for_update_timeout (struct lock_file*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_null_oid (struct object_id const*) ; 
 char const* oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  oideq (struct object_id*,struct object_id const*) ; 
 scalar_t__ read_ref (char const*,struct object_id*) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ write_in_full (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_pseudoref(const char *pseudoref, const struct object_id *oid,
			   const struct object_id *old_oid, struct strbuf *err)
{
	const char *filename;
	int fd;
	struct lock_file lock = LOCK_INIT;
	struct strbuf buf = STRBUF_INIT;
	int ret = -1;

	if (!oid)
		return 0;

	strbuf_addf(&buf, "%s\n", oid_to_hex(oid));

	filename = git_path("%s", pseudoref);
	fd = hold_lock_file_for_update_timeout(&lock, filename, 0,
					       get_files_ref_lock_timeout_ms());
	if (fd < 0) {
		strbuf_addf(err, _("could not open '%s' for writing: %s"),
			    filename, strerror(errno));
		goto done;
	}

	if (old_oid) {
		struct object_id actual_old_oid;

		if (read_ref(pseudoref, &actual_old_oid)) {
			if (!is_null_oid(old_oid)) {
				strbuf_addf(err, _("could not read ref '%s'"),
					    pseudoref);
				rollback_lock_file(&lock);
				goto done;
			}
		} else if (is_null_oid(old_oid)) {
			strbuf_addf(err, _("ref '%s' already exists"),
				    pseudoref);
			rollback_lock_file(&lock);
			goto done;
		} else if (!oideq(&actual_old_oid, old_oid)) {
			strbuf_addf(err, _("unexpected object ID when writing '%s'"),
				    pseudoref);
			rollback_lock_file(&lock);
			goto done;
		}
	}

	if (write_in_full(fd, buf.buf, buf.len) < 0) {
		strbuf_addf(err, _("could not write to '%s'"), filename);
		rollback_lock_file(&lock);
		goto done;
	}

	commit_lock_file(&lock);
	ret = 0;
done:
	strbuf_release(&buf);
	return ret;
}