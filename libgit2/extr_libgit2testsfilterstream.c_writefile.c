#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int CHUNKSIZE ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int p_open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  p_write (int,char*,int) ; 

__attribute__((used)) static void writefile(const char *filename, size_t numchunks)
{
	git_buf path = GIT_BUF_INIT;
	char buf[CHUNKSIZE];
	size_t i = 0, j = 0;
	int fd;

	cl_git_pass(git_buf_joinpath(&path, "empty_standard_repo", filename));

	fd = p_open(path.ptr, O_RDWR|O_CREAT, 0666);
	cl_assert(fd >= 0);

	for (i = 0; i < numchunks; i++) {
		for (j = 0; j < CHUNKSIZE; j++) {
			buf[j] = i % 256;
		}

		cl_git_pass(p_write(fd, buf, CHUNKSIZE));
	}
	p_close(fd);

	git_buf_dispose(&path);
}