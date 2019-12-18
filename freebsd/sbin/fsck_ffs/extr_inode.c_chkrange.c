#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ufs2_daddr_t ;
struct TYPE_7__ {int fs_frag; scalar_t__ fs_fpg; } ;

/* Variables and functions */
 scalar_t__ cgbase (TYPE_1__*,int) ; 
 scalar_t__ cgdmin (TYPE_1__*,int) ; 
 scalar_t__ cgsblock (TYPE_1__*,int) ; 
 scalar_t__ debug ; 
 int dtog (TYPE_1__*,scalar_t__) ; 
 int fragnum (TYPE_1__*,scalar_t__) ; 
 scalar_t__ maxfsblock ; 
 int /*<<< orphan*/  printf (char*,long,long,...) ; 
 TYPE_1__ sblock ; 

int
chkrange(ufs2_daddr_t blk, int cnt)
{
	int c;

	if (cnt <= 0 || blk <= 0 || blk > maxfsblock ||
	    cnt - 1 > maxfsblock - blk)
		return (1);
	if (cnt > sblock.fs_frag ||
	    fragnum(&sblock, blk) + cnt > sblock.fs_frag) {
		if (debug)
			printf("bad size: blk %ld, offset %i, size %d\n",
			    (long)blk, (int)fragnum(&sblock, blk), cnt);
		return (1);
	}
	c = dtog(&sblock, blk);
	if (blk < cgdmin(&sblock, c)) {
		if ((blk + cnt) > cgsblock(&sblock, c)) {
			if (debug) {
				printf("blk %ld < cgdmin %ld;",
				    (long)blk, (long)cgdmin(&sblock, c));
				printf(" blk + cnt %ld > cgsbase %ld\n",
				    (long)(blk + cnt),
				    (long)cgsblock(&sblock, c));
			}
			return (1);
		}
	} else {
		if ((blk + cnt) > cgbase(&sblock, c+1)) {
			if (debug)  {
				printf("blk %ld >= cgdmin %ld;",
				    (long)blk, (long)cgdmin(&sblock, c));
				printf(" blk + cnt %ld > sblock.fs_fpg %ld\n",
				    (long)(blk + cnt), (long)sblock.fs_fpg);
			}
			return (1);
		}
	}
	return (0);
}