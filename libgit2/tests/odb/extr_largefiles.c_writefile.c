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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_stream ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  LARGEFILE_SIZE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_odb_open_wstream (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_stream_finalize_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_stream_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_stream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odb ; 

__attribute__((used)) static void writefile(git_oid *oid)
{
	static git_odb_stream *stream;
	git_buf buf = GIT_BUF_INIT;
	size_t i;

	for (i = 0; i < 3041; i++)
		cl_git_pass(git_buf_puts(&buf, "Hello, world.\n"));

	cl_git_pass(git_odb_open_wstream(&stream, odb, LARGEFILE_SIZE, GIT_OBJECT_BLOB));
	for (i = 0; i < 126103; i++)
		cl_git_pass(git_odb_stream_write(stream, buf.ptr, buf.size));

	cl_git_pass(git_odb_stream_finalize_write(oid, stream));

	git_odb_stream_free(stream);
	git_buf_dispose(&buf);
}