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
typedef  int /*<<< orphan*/  uint64_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  lba_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int fstat (int,struct stat*) ; 
 int image_chunk_skipto (int /*<<< orphan*/ ) ; 
 int image_copyin_mapped (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int image_copyin_stream (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
image_copyin(lba_t blk, int fd, uint64_t *sizep)
{
	struct stat sb;
	int error;

	error = image_chunk_skipto(blk);
	if (!error) {
		if (fstat(fd, &sb) == -1 || !S_ISREG(sb.st_mode))
			error = image_copyin_stream(blk, fd, sizep);
		else
			error = image_copyin_mapped(blk, fd, sizep);
	}
	return (error);
}