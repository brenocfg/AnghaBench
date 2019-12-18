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
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 
 int ncl_writebp (struct buf*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_bwrite(struct buf *bp)
{

	return (ncl_writebp(bp, 1, curthread));
}