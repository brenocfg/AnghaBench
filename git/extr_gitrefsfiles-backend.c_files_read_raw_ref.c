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
struct strbuf {char* buf; } ;
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_size; } ;
struct ref_store {int dummy; } ;
struct object_id {int dummy; } ;
struct files_ref_store {int /*<<< orphan*/  packed_ref_store; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISDIR ; 
 int ENOENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 unsigned int REF_ISBROKEN ; 
 unsigned int REF_ISSYMREF ; 
 int /*<<< orphan*/  REF_STORE_READ ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_refname_format (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 struct files_ref_store* files_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  files_ref_path (struct files_ref_store*,struct strbuf*,char const*) ; 
 scalar_t__ isspace (char const) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_oid_hex (char const*,struct object_id*,char const**) ; 
 scalar_t__ refs_read_raw_ref (int /*<<< orphan*/ ,char const*,struct object_id*,struct strbuf*,unsigned int*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 scalar_t__ strbuf_read (struct strbuf*,int,int) ; 
 scalar_t__ strbuf_readlink (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 

__attribute__((used)) static int files_read_raw_ref(struct ref_store *ref_store,
			      const char *refname, struct object_id *oid,
			      struct strbuf *referent, unsigned int *type)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_READ, "read_raw_ref");
	struct strbuf sb_contents = STRBUF_INIT;
	struct strbuf sb_path = STRBUF_INIT;
	const char *path;
	const char *buf;
	const char *p;
	struct stat st;
	int fd;
	int ret = -1;
	int save_errno;
	int remaining_retries = 3;

	*type = 0;
	strbuf_reset(&sb_path);

	files_ref_path(refs, &sb_path, refname);

	path = sb_path.buf;

stat_ref:
	/*
	 * We might have to loop back here to avoid a race
	 * condition: first we lstat() the file, then we try
	 * to read it as a link or as a file.  But if somebody
	 * changes the type of the file (file <-> directory
	 * <-> symlink) between the lstat() and reading, then
	 * we don't want to report that as an error but rather
	 * try again starting with the lstat().
	 *
	 * We'll keep a count of the retries, though, just to avoid
	 * any confusing situation sending us into an infinite loop.
	 */

	if (remaining_retries-- <= 0)
		goto out;

	if (lstat(path, &st) < 0) {
		if (errno != ENOENT)
			goto out;
		if (refs_read_raw_ref(refs->packed_ref_store, refname,
				      oid, referent, type)) {
			errno = ENOENT;
			goto out;
		}
		ret = 0;
		goto out;
	}

	/* Follow "normalized" - ie "refs/.." symlinks by hand */
	if (S_ISLNK(st.st_mode)) {
		strbuf_reset(&sb_contents);
		if (strbuf_readlink(&sb_contents, path, st.st_size) < 0) {
			if (errno == ENOENT || errno == EINVAL)
				/* inconsistent with lstat; retry */
				goto stat_ref;
			else
				goto out;
		}
		if (starts_with(sb_contents.buf, "refs/") &&
		    !check_refname_format(sb_contents.buf, 0)) {
			strbuf_swap(&sb_contents, referent);
			*type |= REF_ISSYMREF;
			ret = 0;
			goto out;
		}
		/*
		 * It doesn't look like a refname; fall through to just
		 * treating it like a non-symlink, and reading whatever it
		 * points to.
		 */
	}

	/* Is it a directory? */
	if (S_ISDIR(st.st_mode)) {
		/*
		 * Even though there is a directory where the loose
		 * ref is supposed to be, there could still be a
		 * packed ref:
		 */
		if (refs_read_raw_ref(refs->packed_ref_store, refname,
				      oid, referent, type)) {
			errno = EISDIR;
			goto out;
		}
		ret = 0;
		goto out;
	}

	/*
	 * Anything else, just open it and try to use it as
	 * a ref
	 */
	fd = open(path, O_RDONLY);
	if (fd < 0) {
		if (errno == ENOENT && !S_ISLNK(st.st_mode))
			/* inconsistent with lstat; retry */
			goto stat_ref;
		else
			goto out;
	}
	strbuf_reset(&sb_contents);
	if (strbuf_read(&sb_contents, fd, 256) < 0) {
		int save_errno = errno;
		close(fd);
		errno = save_errno;
		goto out;
	}
	close(fd);
	strbuf_rtrim(&sb_contents);
	buf = sb_contents.buf;
	if (starts_with(buf, "ref:")) {
		buf += 4;
		while (isspace(*buf))
			buf++;

		strbuf_reset(referent);
		strbuf_addstr(referent, buf);
		*type |= REF_ISSYMREF;
		ret = 0;
		goto out;
	}

	/*
	 * Please note that FETCH_HEAD has additional
	 * data after the sha.
	 */
	if (parse_oid_hex(buf, oid, &p) ||
	    (*p != '\0' && !isspace(*p))) {
		*type |= REF_ISBROKEN;
		errno = EINVAL;
		goto out;
	}

	ret = 0;

out:
	save_errno = errno;
	strbuf_release(&sb_path);
	strbuf_release(&sb_contents);
	errno = save_errno;
	return ret;
}