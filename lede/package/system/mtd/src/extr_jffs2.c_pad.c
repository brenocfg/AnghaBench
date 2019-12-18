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

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ buf ; 
 int erasesize ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 scalar_t__ mtd_block_is_bad (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mtd_erase_block (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mtdofs ; 
 scalar_t__ mtdsize ; 
 int ofs ; 
 int /*<<< orphan*/  outfd ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void pad(int size)
{
	if ((ofs % size == 0) && (ofs < erasesize))
		return;

	if (ofs < erasesize) {
		memset(buf + ofs, 0xff, (size - (ofs % size)));
		ofs += (size - (ofs % size));
	}
	ofs = ofs % erasesize;
	if (ofs == 0) {
		while (mtd_block_is_bad(outfd, mtdofs) && (mtdofs < mtdsize)) {
			if (!quiet)
				fprintf(stderr, "\nSkipping bad block at 0x%08x   ", mtdofs);

			mtdofs += erasesize;

			/* Move the file pointer along over the bad block. */
			lseek(outfd, erasesize, SEEK_CUR);
		}
		mtd_erase_block(outfd, mtdofs);
		write(outfd, buf, erasesize);
		mtdofs += erasesize;
	}
}