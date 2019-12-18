#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  io_flags; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_GET_PSIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dsl_pool_sync_context (TYPE_2__*) ; 
 int /*<<< orphan*/  zio_free_sync (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 

void
dsl_free_sync(zio_t *pio, dsl_pool_t *dp, uint64_t txg, const blkptr_t *bpp)
{
	ASSERT(dsl_pool_sync_context(dp));
	zio_nowait(zio_free_sync(pio, dp->dp_spa, txg, bpp, BP_GET_PSIZE(bpp),
	    pio->io_flags));
}