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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  assertion_file_mode (char const*,int,char const*,int) ; 
 scalar_t__ chmod (char const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fwrite (void const*,int,size_t,int /*<<< orphan*/ *) ; 
 int open (char const*,int,int) ; 
 size_t strlen (void const*) ; 
 scalar_t__ write (int,void const*,scalar_t__) ; 

int
assertion_make_file(const char *file, int line,
    const char *path, int mode, int csize, const void *contents)
{
#if defined(_WIN32) && !defined(__CYGWIN__)
	/* TODO: Rework this to set file mode as well. */
	FILE *f;
	(void)mode; /* UNUSED */
	assertion_count(file, line);
	f = fopen(path, "wb");
	if (f == NULL) {
		failure_start(file, line, "Could not create file %s", path);
		failure_finish(NULL);
		return (0);
	}
	if (contents != NULL) {
		size_t wsize;

		if (csize < 0)
			wsize = strlen(contents);
		else
			wsize = (size_t)csize;
		if (wsize != fwrite(contents, 1, wsize, f)) {
			fclose(f);
			failure_start(file, line,
			    "Could not write file %s", path);
			failure_finish(NULL);
			return (0);
		}
	}
	fclose(f);
	return (1);
#else
	int fd;
	assertion_count(file, line);
	fd = open(path, O_CREAT | O_WRONLY, mode >= 0 ? mode : 0644);
	if (fd < 0) {
		failure_start(file, line, "Could not create %s", path);
		failure_finish(NULL);
		return (0);
	}
	if (0 != chmod(path, mode)) {
		failure_start(file, line, "Could not chmod %s", path);
		failure_finish(NULL);
		close(fd);
		return (0);
	}
	if (contents != NULL) {
		ssize_t wsize;

		if (csize < 0)
			wsize = (ssize_t)strlen(contents);
		else
			wsize = (ssize_t)csize;
		if (wsize != write(fd, contents, wsize)) {
			close(fd);
			failure_start(file, line,
			    "Could not write to %s", path);
			failure_finish(NULL);
			close(fd);
			return (0);
		}
	}
	close(fd);
	assertion_file_mode(file, line, path, mode);
	return (1);
#endif
}