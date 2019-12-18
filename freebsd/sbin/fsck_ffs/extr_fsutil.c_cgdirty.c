#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cg {scalar_t__ cg_ckhash; } ;
struct TYPE_3__ {struct cg* b_cg; } ;
struct bufarea {TYPE_1__ b_un; } ;
struct TYPE_4__ {int fs_metackhash; int /*<<< orphan*/  fs_cgsize; } ;

/* Variables and functions */
 int CK_CYLGRP ; 
 scalar_t__ calculate_crc32c (long,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirty (struct bufarea*) ; 
 TYPE_2__ sblock ; 

void
cgdirty(struct bufarea *cgbp)
{
	struct cg *cg;

	cg = cgbp->b_un.b_cg;
	if ((sblock.fs_metackhash & CK_CYLGRP) != 0) {
		cg->cg_ckhash = 0;
		cg->cg_ckhash =
		    calculate_crc32c(~0L, (void *)cg, sblock.fs_cgsize);
	}
	dirty(cgbp);
}