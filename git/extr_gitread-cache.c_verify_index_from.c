#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct index_state {TYPE_1__ oid; int /*<<< orphan*/  initialized; } ;
struct cache_header {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {scalar_t__ rawsz; } ;

/* Variables and functions */
 int GIT_MAX_RAWSZ ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  hasheq (int /*<<< orphan*/ ,unsigned char*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ pread_in_full (int,unsigned char*,scalar_t__,scalar_t__) ; 
 TYPE_2__* the_hash_algo ; 

__attribute__((used)) static int verify_index_from(const struct index_state *istate, const char *path)
{
	int fd;
	ssize_t n;
	struct stat st;
	unsigned char hash[GIT_MAX_RAWSZ];

	if (!istate->initialized)
		return 0;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return 0;

	if (fstat(fd, &st))
		goto out;

	if (st.st_size < sizeof(struct cache_header) + the_hash_algo->rawsz)
		goto out;

	n = pread_in_full(fd, hash, the_hash_algo->rawsz, st.st_size - the_hash_algo->rawsz);
	if (n != the_hash_algo->rawsz)
		goto out;

	if (!hasheq(istate->oid.hash, hash))
		goto out;

	close(fd);
	return 1;

out:
	close(fd);
	return 0;
}