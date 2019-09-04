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
struct object_id {int dummy; } ;
struct git_istream {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int OBJ_BLOB ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  close_istream (struct git_istream*) ; 
 int /*<<< orphan*/  free_stream_filter (struct stream_filter*) ; 
 scalar_t__ lseek (int,int,int /*<<< orphan*/ ) ; 
 struct git_istream* open_istream (struct object_id const*,int*,unsigned long*,struct stream_filter*) ; 
 int read_istream (struct git_istream*,char*,int) ; 
 int write_in_full (int,char*,int) ; 
 int xwrite (int,char*,int) ; 

int stream_blob_to_fd(int fd, const struct object_id *oid, struct stream_filter *filter,
		      int can_seek)
{
	struct git_istream *st;
	enum object_type type;
	unsigned long sz;
	ssize_t kept = 0;
	int result = -1;

	st = open_istream(oid, &type, &sz, filter);
	if (!st) {
		if (filter)
			free_stream_filter(filter);
		return result;
	}
	if (type != OBJ_BLOB)
		goto close_and_exit;
	for (;;) {
		char buf[1024 * 16];
		ssize_t wrote, holeto;
		ssize_t readlen = read_istream(st, buf, sizeof(buf));

		if (readlen < 0)
			goto close_and_exit;
		if (!readlen)
			break;
		if (can_seek && sizeof(buf) == readlen) {
			for (holeto = 0; holeto < readlen; holeto++)
				if (buf[holeto])
					break;
			if (readlen == holeto) {
				kept += holeto;
				continue;
			}
		}

		if (kept && lseek(fd, kept, SEEK_CUR) == (off_t) -1)
			goto close_and_exit;
		else
			kept = 0;
		wrote = write_in_full(fd, buf, readlen);

		if (wrote < 0)
			goto close_and_exit;
	}
	if (kept && (lseek(fd, kept - 1, SEEK_CUR) == (off_t) -1 ||
		     xwrite(fd, "", 1) != 1))
		goto close_and_exit;
	result = 0;

 close_and_exit:
	close_istream(st);
	return result;
}