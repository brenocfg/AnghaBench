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
 int git_mkstemp_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_path_buf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  safe_create_leading_directories (int /*<<< orphan*/ ) ; 
 int xmkstemp_mode (int /*<<< orphan*/ ,int) ; 

int odb_mkstemp(struct strbuf *temp_filename, const char *pattern)
{
	int fd;
	/*
	 * we let the umask do its job, don't try to be more
	 * restrictive except to remove write permission.
	 */
	int mode = 0444;
	git_path_buf(temp_filename, "objects/%s", pattern);
	fd = git_mkstemp_mode(temp_filename->buf, mode);
	if (0 <= fd)
		return fd;

	/* slow path */
	/* some mkstemp implementations erase temp_filename on failure */
	git_path_buf(temp_filename, "objects/%s", pattern);
	safe_create_leading_directories(temp_filename->buf);
	return xmkstemp_mode(temp_filename->buf, mode);
}