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
struct strbuf {unsigned long len; char* buf; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct apply_state {TYPE_1__* repo; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISGITLINK (unsigned int) ; 
 scalar_t__ S_ISLNK (unsigned int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ close (int) ; 
 scalar_t__ convert_to_working_tree (int /*<<< orphan*/ ,char const*,char const*,unsigned long,struct strbuf*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ has_symlinks ; 
 int /*<<< orphan*/  lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  mkdir (char const*,int) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  symlink (char const*,char const*) ; 
 scalar_t__ write_in_full (int,char const*,unsigned long) ; 

__attribute__((used)) static int try_create_file(struct apply_state *state, const char *path,
			   unsigned int mode, const char *buf,
			   unsigned long size)
{
	int fd, res;
	struct strbuf nbuf = STRBUF_INIT;

	if (S_ISGITLINK(mode)) {
		struct stat st;
		if (!lstat(path, &st) && S_ISDIR(st.st_mode))
			return 0;
		return !!mkdir(path, 0777);
	}

	if (has_symlinks && S_ISLNK(mode))
		/* Although buf:size is counted string, it also is NUL
		 * terminated.
		 */
		return !!symlink(buf, path);

	fd = open(path, O_CREAT | O_EXCL | O_WRONLY, (mode & 0100) ? 0777 : 0666);
	if (fd < 0)
		return 1;

	if (convert_to_working_tree(state->repo->index, path, buf, size, &nbuf)) {
		size = nbuf.len;
		buf  = nbuf.buf;
	}

	res = write_in_full(fd, buf, size) < 0;
	if (res)
		error_errno(_("failed to write to '%s'"), path);
	strbuf_release(&nbuf);

	if (close(fd) < 0 && !res)
		return error_errno(_("closing file '%s'"), path);

	return res ? -1 : 0;
}