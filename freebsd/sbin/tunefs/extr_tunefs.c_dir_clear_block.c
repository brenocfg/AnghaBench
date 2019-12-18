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
struct direct {int /*<<< orphan*/  d_type; scalar_t__ d_reclen; scalar_t__ d_ino; } ;
typedef  size_t off_t ;
struct TYPE_2__ {size_t fs_bsize; } ;

/* Variables and functions */
 scalar_t__ DIRBLKSIZ ; 
 int /*<<< orphan*/  DT_UNKNOWN ; 
 TYPE_1__ sblock ; 

__attribute__((used)) static void
dir_clear_block(const char *block, off_t off)
{
	struct direct *dp;

	for (; off < sblock.fs_bsize; off += DIRBLKSIZ) {
		dp = (struct direct *)&block[off];
		dp->d_ino = 0;
		dp->d_reclen = DIRBLKSIZ;
		dp->d_type = DT_UNKNOWN;
	}
}