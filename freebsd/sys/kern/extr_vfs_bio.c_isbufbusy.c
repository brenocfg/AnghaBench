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
struct buf {int b_flags; } ;

/* Variables and functions */
 scalar_t__ BUF_ISLOCKED (struct buf*) ; 
 int B_DELWRI ; 
 int B_INVAL ; 

__attribute__((used)) static int
isbufbusy(struct buf *bp)
{
	if (((bp->b_flags & B_INVAL) == 0 && BUF_ISLOCKED(bp)) ||
	    ((bp->b_flags & (B_DELWRI | B_INVAL)) == B_DELWRI))
		return (1);
	return (0);
}