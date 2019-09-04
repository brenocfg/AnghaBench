#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_11__ {int (* write ) (TYPE_1__*,char*,scalar_t__) ;int (* close ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ git_writestream ;
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_filter_list ;
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int FILTERIO_BUFSIZE ; 
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_VECTOR_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_futils_open_ro (int /*<<< orphan*/ ) ; 
 int git_path_join_unrooted (TYPE_2__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 char* git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_close (int) ; 
 scalar_t__ p_read (int,char*,int) ; 
 int /*<<< orphan*/  stream_list_free (int /*<<< orphan*/ *) ; 
 int stream_list_init (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int stub1 (TYPE_1__*,char*,scalar_t__) ; 
 int stub2 (TYPE_1__*) ; 

int git_filter_list_stream_file(
	git_filter_list *filters,
	git_repository *repo,
	const char *path,
	git_writestream *target)
{
	char buf[FILTERIO_BUFSIZE];
	git_buf abspath = GIT_BUF_INIT;
	const char *base = repo ? git_repository_workdir(repo) : NULL;
	git_vector filter_streams = GIT_VECTOR_INIT;
	git_writestream *stream_start;
	ssize_t readlen;
	int fd = -1, error, initialized = 0;

	if ((error = stream_list_init(
			&stream_start, &filter_streams, filters, target)) < 0 ||
		(error = git_path_join_unrooted(&abspath, path, base, NULL)) < 0)
		goto done;
	initialized = 1;

	if ((fd = git_futils_open_ro(abspath.ptr)) < 0) {
		error = fd;
		goto done;
	}

	while ((readlen = p_read(fd, buf, sizeof(buf))) > 0) {
		if ((error = stream_start->write(stream_start, buf, readlen)) < 0)
			goto done;
	}

	if (readlen < 0)
		error = -1;

done:
	if (initialized)
		error |= stream_start->close(stream_start);

	if (fd >= 0)
		p_close(fd);
	stream_list_free(&filter_streams);
	git_buf_dispose(&abspath);
	return error;
}