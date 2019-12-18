#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ ddk_prop; int /*<<< orphan*/  ddk_cksum; } ;
typedef  TYPE_1__ ddt_key_t ;
struct TYPE_12__ {int /*<<< orphan*/  blk_cksum; } ;
typedef  TYPE_2__ blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_GET_COMPRESS (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BP_GET_LSIZE (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BP_GET_PSIZE (TYPE_2__ const*) ; 
 int /*<<< orphan*/  DDK_SET_COMPRESS (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DDK_SET_LSIZE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DDK_SET_PSIZE (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
ddt_key_fill(ddt_key_t *ddk, const blkptr_t *bp)
{
	ddk->ddk_cksum = bp->blk_cksum;
	ddk->ddk_prop = 0;

	DDK_SET_LSIZE(ddk, BP_GET_LSIZE(bp));
	DDK_SET_PSIZE(ddk, BP_GET_PSIZE(bp));
	DDK_SET_COMPRESS(ddk, BP_GET_COMPRESS(bp));
}