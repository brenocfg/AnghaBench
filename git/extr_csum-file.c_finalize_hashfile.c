#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hashfile {scalar_t__ fd; scalar_t__ check_fd; int /*<<< orphan*/  name; int /*<<< orphan*/  buffer; int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  rawsz; int /*<<< orphan*/  (* final_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 unsigned int CSUM_CLOSE ; 
 unsigned int CSUM_FSYNC ; 
 unsigned int CSUM_HASH_IN_STREAM ; 
 scalar_t__ close (scalar_t__) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush (struct hashfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct hashfile*) ; 
 int /*<<< orphan*/  fsync_or_die (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashcpy (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashflush (struct hashfile*) ; 
 int read_in_full (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* the_hash_algo ; 

int finalize_hashfile(struct hashfile *f, unsigned char *result, unsigned int flags)
{
	int fd;

	hashflush(f);
	the_hash_algo->final_fn(f->buffer, &f->ctx);
	if (result)
		hashcpy(result, f->buffer);
	if (flags & CSUM_HASH_IN_STREAM)
		flush(f, f->buffer, the_hash_algo->rawsz);
	if (flags & CSUM_FSYNC)
		fsync_or_die(f->fd, f->name);
	if (flags & CSUM_CLOSE) {
		if (close(f->fd))
			die_errno("%s: sha1 file error on close", f->name);
		fd = 0;
	} else
		fd = f->fd;
	if (0 <= f->check_fd) {
		char discard;
		int cnt = read_in_full(f->check_fd, &discard, 1);
		if (cnt < 0)
			die_errno("%s: error when reading the tail of sha1 file",
				  f->name);
		if (cnt)
			die("%s: sha1 file has trailing garbage", f->name);
		if (close(f->check_fd))
			die_errno("%s: sha1 file error on close", f->name);
	}
	free(f);
	return fd;
}