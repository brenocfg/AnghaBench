#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * b_buf; } ;
struct TYPE_6__ {TYPE_1__ b_un; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_SUPERBLK ; 
 int /*<<< orphan*/  DEV_BSIZE ; 
 int /*<<< orphan*/  EEXIT ; 
 void* Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBLOCKSIZE ; 
 TYPE_2__ asblk ; 
 int /*<<< orphan*/  dev_bsize ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fsmodified ; 
 int fswritefd ; 
 int /*<<< orphan*/  initbarea (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lfdir ; 
 TYPE_2__ sblk ; 
 int /*<<< orphan*/  secsize ; 

void
sblock_init(void)
{

	fswritefd = -1;
	fsmodified = 0;
	lfdir = 0;
	initbarea(&sblk, BT_SUPERBLK);
	initbarea(&asblk, BT_SUPERBLK);
	sblk.b_un.b_buf = Malloc(SBLOCKSIZE);
	asblk.b_un.b_buf = Malloc(SBLOCKSIZE);
	if (sblk.b_un.b_buf == NULL || asblk.b_un.b_buf == NULL)
		errx(EEXIT, "cannot allocate space for superblock");
	dev_bsize = secsize = DEV_BSIZE;
}