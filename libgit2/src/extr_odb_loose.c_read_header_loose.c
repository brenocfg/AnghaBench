#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  obj ;
struct TYPE_8__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ git_rawobj ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_ZLIB ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git_buf_oom (TYPE_2__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_futils_open_ro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_typeisloose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zlib_compressed_data (unsigned char*,size_t) ; 
 int /*<<< orphan*/  p_close (int) ; 
 scalar_t__ p_read (int,unsigned char*,int) ; 
 int read_header_loose_packlike (TYPE_1__*,unsigned char*,size_t) ; 
 int read_header_loose_standard (TYPE_1__*,unsigned char*,size_t) ; 

__attribute__((used)) static int read_header_loose(git_rawobj *out, git_buf *loc)
{
	unsigned char obj[1024];
	ssize_t obj_len;
	int fd, error;

	assert(out && loc);

	if (git_buf_oom(loc))
		return -1;

	out->data = NULL;

	if ((error = fd = git_futils_open_ro(loc->ptr)) < 0)
		goto done;

	if ((obj_len = p_read(fd, obj, sizeof(obj))) < 0) {
		error = (int)obj_len;
		goto done;
	}

	if (!is_zlib_compressed_data(obj, (size_t)obj_len))
		error = read_header_loose_packlike(out, obj, (size_t)obj_len);
	else
		error = read_header_loose_standard(out, obj, (size_t)obj_len);

	if (!error && !git_object_typeisloose(out->type)) {
		git_error_set(GIT_ERROR_ZLIB, "failed to read loose object header");
		error = -1;
		goto done;
	}

done:
	if (fd >= 0)
		p_close(fd);
	return error;
}