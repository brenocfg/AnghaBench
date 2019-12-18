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
typedef  scalar_t__ ufs2_daddr_t ;
struct uufsd {scalar_t__ d_bsize; int /*<<< orphan*/  d_fd; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct uufsd*,char*) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int pwrite (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
berase_helper(struct uufsd *disk, ufs2_daddr_t blockno, ufs2_daddr_t size)
{
	char *zero_chunk;
	off_t offset, zero_chunk_size, pwrite_size;
	int rv;

	offset = blockno * disk->d_bsize;
	zero_chunk_size = 65536 * disk->d_bsize;
	zero_chunk = calloc(1, zero_chunk_size);
	if (zero_chunk == NULL) {
		ERROR(disk, "failed to allocate memory");
		return (-1);
	}
	while (size > 0) { 
		pwrite_size = size;
		if (pwrite_size > zero_chunk_size)
			pwrite_size = zero_chunk_size;
		rv = pwrite(disk->d_fd, zero_chunk, pwrite_size, offset);
		if (rv == -1) {
			ERROR(disk, "failed writing to disk");
			break;
		}
		size -= rv;
		offset += rv;
		rv = 0;
	}
	free(zero_chunk);
	return (rv);
}