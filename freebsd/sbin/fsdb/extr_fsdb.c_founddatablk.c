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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ curinum ; 
 scalar_t__ findblk_numtofind ; 
 scalar_t__ fsbtodb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sblock ; 

__attribute__((used)) static int
founddatablk(uint64_t blk)
{

    printf("%llu: data block of inode %ju\n",
	(unsigned long long)fsbtodb(&sblock, blk), (uintmax_t)curinum);
    findblk_numtofind--;
    if (findblk_numtofind == 0)
	return 1;
    return 0;
}