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
struct cg {scalar_t__ cg_ckhash; } ;
struct TYPE_2__ {int fs_metackhash; int /*<<< orphan*/  fs_cgsize; } ;

/* Variables and functions */
 int CK_CYLGRP ; 
 scalar_t__ calculate_crc32c (long,void*,int /*<<< orphan*/ ) ; 
 TYPE_1__ sblock ; 

__attribute__((used)) static void
cgckhash(struct cg *cgp)
{

	if ((sblock.fs_metackhash & CK_CYLGRP) == 0)
		return;
	cgp->cg_ckhash = 0;
	cgp->cg_ckhash = calculate_crc32c(~0L, (void *)cgp, sblock.fs_cgsize);
}