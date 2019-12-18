#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_joinpath (TYPE_1__*,char const*,char const*) ; 
 int git_futils_writebuffer (TYPE_1__ const*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int write_wtfile(const char *base, const char *file, const git_buf *buf)
{
	git_buf path = GIT_BUF_INIT;
	int err;

	assert(base && file && buf);

	if ((err = git_buf_joinpath(&path, base, file)) < 0)
		goto out;

	if ((err = git_futils_writebuffer(buf, path.ptr, O_CREAT|O_EXCL|O_WRONLY, 0644)) < 0)
		goto out;

out:
	git_buf_dispose(&path);

	return err;
}