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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_2__ {int blkno; int len; scalar_t__ offset; } ;
struct mkuz_blk {TYPE_1__ info; int /*<<< orphan*/  data; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 struct mkuz_blk* MKUZ_BLK_EOF ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (struct mkuz_blk*) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mkuz_blk* mkuz_blk_ctor (int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mkuz_blk *
readblock(int fd, u_int32_t clstsize)
{
	int numread;
	struct mkuz_blk *rval;
	static int blockcnt;
	off_t cpos;

	rval = mkuz_blk_ctor(clstsize);

	rval->info.blkno = blockcnt;
	blockcnt += 1;
	cpos = lseek(fd, 0, SEEK_CUR);
	if (cpos < 0) {
		err(1, "readblock: lseek() failed");
		/* Not reached */
	}
	rval->info.offset = cpos;

	numread = read(fd, rval->data, clstsize);
	if (numread < 0) {
		err(1, "readblock: read() failed");
		/* Not reached */
	}
	if (numread == 0) {
		free(rval);
		return MKUZ_BLK_EOF;
	}
	rval->info.len = numread;
	return rval;
}