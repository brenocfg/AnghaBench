#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_joinpath (TYPE_1__*,char const*,char const*) ; 
 int git_futils_readbuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int loose_readbuffer(git_buf *buf, const char *base, const char *path)
{
	int error;

	/* build full path to file */
	if ((error = git_buf_joinpath(buf, base, path)) < 0 ||
		(error = git_futils_readbuffer(buf, buf->ptr)) < 0)
		git_buf_dispose(buf);

	return error;
}