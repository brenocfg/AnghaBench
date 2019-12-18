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
struct strbuf {scalar_t__ len; } ;
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_size; } ;
struct repository {int /*<<< orphan*/  index; } ;
struct diff_filespec {char* data; scalar_t__ size; int should_free; int is_binary; int should_munmap; int /*<<< orphan*/  oid; int /*<<< orphan*/  path; int /*<<< orphan*/  oid_valid; int /*<<< orphan*/  mode; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 unsigned int CHECK_BINARY ; 
 unsigned int CHECK_SIZE_ONLY ; 
 int CONV_EOL_RNDTRP_DIE ; 
 int CONV_EOL_RNDTRP_WARN ; 
 int /*<<< orphan*/  DIFF_FILE_VALID (struct diff_filespec*) ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ big_file_threshold ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ convert_to_git (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,struct strbuf*,int) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int diff_populate_gitlink (struct diff_filespec*,int) ; 
 int global_conv_flags_eol ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  munmap (char*,scalar_t__) ; 
 int oid_object_info (struct repository*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* read_object_file (int /*<<< orphan*/ *,int*,scalar_t__*) ; 
 scalar_t__ reuse_worktree_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* strbuf_detach (struct strbuf*,size_t*) ; 
 scalar_t__ strbuf_readlink (struct strbuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  would_convert_to_git (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* xmmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xsize_t (int /*<<< orphan*/ ) ; 

int diff_populate_filespec(struct repository *r,
			   struct diff_filespec *s,
			   unsigned int flags)
{
	int size_only = flags & CHECK_SIZE_ONLY;
	int err = 0;
	int conv_flags = global_conv_flags_eol;
	/*
	 * demote FAIL to WARN to allow inspecting the situation
	 * instead of refusing.
	 */
	if (conv_flags & CONV_EOL_RNDTRP_DIE)
		conv_flags = CONV_EOL_RNDTRP_WARN;

	if (!DIFF_FILE_VALID(s))
		die("internal error: asking to populate invalid file.");
	if (S_ISDIR(s->mode))
		return -1;

	if (s->data)
		return 0;

	if (size_only && 0 < s->size)
		return 0;

	if (S_ISGITLINK(s->mode))
		return diff_populate_gitlink(s, size_only);

	if (!s->oid_valid ||
	    reuse_worktree_file(r->index, s->path, &s->oid, 0)) {
		struct strbuf buf = STRBUF_INIT;
		struct stat st;
		int fd;

		if (lstat(s->path, &st) < 0) {
		err_empty:
			err = -1;
		empty:
			s->data = (char *)"";
			s->size = 0;
			return err;
		}
		s->size = xsize_t(st.st_size);
		if (!s->size)
			goto empty;
		if (S_ISLNK(st.st_mode)) {
			struct strbuf sb = STRBUF_INIT;

			if (strbuf_readlink(&sb, s->path, s->size))
				goto err_empty;
			s->size = sb.len;
			s->data = strbuf_detach(&sb, NULL);
			s->should_free = 1;
			return 0;
		}

		/*
		 * Even if the caller would be happy with getting
		 * only the size, we cannot return early at this
		 * point if the path requires us to run the content
		 * conversion.
		 */
		if (size_only && !would_convert_to_git(r->index, s->path))
			return 0;

		/*
		 * Note: this check uses xsize_t(st.st_size) that may
		 * not be the true size of the blob after it goes
		 * through convert_to_git().  This may not strictly be
		 * correct, but the whole point of big_file_threshold
		 * and is_binary check being that we want to avoid
		 * opening the file and inspecting the contents, this
		 * is probably fine.
		 */
		if ((flags & CHECK_BINARY) &&
		    s->size > big_file_threshold && s->is_binary == -1) {
			s->is_binary = 1;
			return 0;
		}
		fd = open(s->path, O_RDONLY);
		if (fd < 0)
			goto err_empty;
		s->data = xmmap(NULL, s->size, PROT_READ, MAP_PRIVATE, fd, 0);
		close(fd);
		s->should_munmap = 1;

		/*
		 * Convert from working tree format to canonical git format
		 */
		if (convert_to_git(r->index, s->path, s->data, s->size, &buf, conv_flags)) {
			size_t size = 0;
			munmap(s->data, s->size);
			s->should_munmap = 0;
			s->data = strbuf_detach(&buf, &size);
			s->size = size;
			s->should_free = 1;
		}
	}
	else {
		enum object_type type;
		if (size_only || (flags & CHECK_BINARY)) {
			type = oid_object_info(r, &s->oid, &s->size);
			if (type < 0)
				die("unable to read %s",
				    oid_to_hex(&s->oid));
			if (size_only)
				return 0;
			if (s->size > big_file_threshold && s->is_binary == -1) {
				s->is_binary = 1;
				return 0;
			}
		}
		s->data = read_object_file(&s->oid, &type, &s->size);
		if (!s->data)
			die("unable to read %s", oid_to_hex(&s->oid));
		s->should_free = 1;
	}
	return 0;
}