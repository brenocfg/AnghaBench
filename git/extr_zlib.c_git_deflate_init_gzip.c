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
typedef  int /*<<< orphan*/  git_zstream ;

/* Variables and functions */
 int /*<<< orphan*/  do_git_deflate_init (int /*<<< orphan*/ *,int,int) ; 

void git_deflate_init_gzip(git_zstream *strm, int level)
{
	/*
	 * Use default 15 bits, +16 is to generate gzip header/trailer
	 * instead of the zlib wrapper.
	 */
	do_git_deflate_init(strm, level, 15 + 16);
}