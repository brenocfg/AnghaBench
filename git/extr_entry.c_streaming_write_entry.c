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
struct stream_filter {int dummy; } ;
struct stat {int dummy; } ;
struct checkout {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int close (int) ; 
 int fstat_output (int,struct checkout const*,struct stat*) ; 
 int open_output_fd (char*,struct cache_entry const*,int) ; 
 int stream_blob_to_fd (int,int /*<<< orphan*/ *,struct stream_filter*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int streaming_write_entry(const struct cache_entry *ce, char *path,
				 struct stream_filter *filter,
				 const struct checkout *state, int to_tempfile,
				 int *fstat_done, struct stat *statbuf)
{
	int result = 0;
	int fd;

	fd = open_output_fd(path, ce, to_tempfile);
	if (fd < 0)
		return -1;

	result |= stream_blob_to_fd(fd, &ce->oid, filter, 1);
	*fstat_done = fstat_output(fd, state, statbuf);
	result |= close(fd);

	if (result)
		unlink(path);
	return result;
}