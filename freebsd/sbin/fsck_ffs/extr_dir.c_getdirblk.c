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
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct bufarea {int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DIRDATA ; 
 int /*<<< orphan*/  B_INUSE ; 
 struct bufarea* getdatablk (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 struct bufarea* pdirbp ; 

__attribute__((used)) static struct bufarea *
getdirblk(ufs2_daddr_t blkno, long size)
{

	if (pdirbp != NULL)
		pdirbp->b_flags &= ~B_INUSE;
	pdirbp = getdatablk(blkno, size, BT_DIRDATA);
	return (pdirbp);
}