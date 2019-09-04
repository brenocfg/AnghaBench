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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct object_id {int dummy; } ;
struct index_state {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_BLOB ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ big_file_threshold ; 
 int /*<<< orphan*/  close (int) ; 
 int index_core (struct index_state*,struct object_id*,int,int /*<<< orphan*/ ,int,char const*,unsigned int) ; 
 int index_pipe (struct index_state*,struct object_id*,int,int,char const*,unsigned int) ; 
 int index_stream (struct object_id*,int,int /*<<< orphan*/ ,int,char const*,unsigned int) ; 
 int index_stream_convert_blob (struct index_state*,struct object_id*,int,char const*,unsigned int) ; 
 scalar_t__ would_convert_to_git (struct index_state*,char const*) ; 
 scalar_t__ would_convert_to_git_filter_fd (struct index_state*,char const*) ; 
 int /*<<< orphan*/  xsize_t (scalar_t__) ; 

int index_fd(struct index_state *istate, struct object_id *oid,
	     int fd, struct stat *st,
	     enum object_type type, const char *path, unsigned flags)
{
	int ret;

	/*
	 * Call xsize_t() only when needed to avoid potentially unnecessary
	 * die() for large files.
	 */
	if (type == OBJ_BLOB && path && would_convert_to_git_filter_fd(istate, path))
		ret = index_stream_convert_blob(istate, oid, fd, path, flags);
	else if (!S_ISREG(st->st_mode))
		ret = index_pipe(istate, oid, fd, type, path, flags);
	else if (st->st_size <= big_file_threshold || type != OBJ_BLOB ||
		 (path && would_convert_to_git(istate, path)))
		ret = index_core(istate, oid, fd, xsize_t(st->st_size),
				 type, path, flags);
	else
		ret = index_stream(oid, fd, xsize_t(st->st_size), type, path,
				   flags);
	close(fd);
	return ret;
}