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

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 scalar_t__ adjust_shared_perm (int /*<<< orphan*/ ) ; 
 int directory_size (char const*) ; 
 scalar_t__ errno ; 
 int git_mkstemp_mode (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mkdir (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static int create_tmpfile(struct strbuf *tmp, const char *filename)
{
	int fd, dirlen = directory_size(filename);

	strbuf_reset(tmp);
	strbuf_add(tmp, filename, dirlen);
	strbuf_addstr(tmp, "tmp_obj_XXXXXX");
	fd = git_mkstemp_mode(tmp->buf, 0444);
	if (fd < 0 && dirlen && errno == ENOENT) {
		/*
		 * Make sure the directory exists; note that the contents
		 * of the buffer are undefined after mkstemp returns an
		 * error, so we have to rewrite the whole buffer from
		 * scratch.
		 */
		strbuf_reset(tmp);
		strbuf_add(tmp, filename, dirlen - 1);
		if (mkdir(tmp->buf, 0777) && errno != EEXIST)
			return -1;
		if (adjust_shared_perm(tmp->buf))
			return -1;

		/* Try again */
		strbuf_addstr(tmp, "/tmp_obj_XXXXXX");
		fd = git_mkstemp_mode(tmp->buf, 0444);
	}
	return fd;
}