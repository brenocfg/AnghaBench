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
struct TYPE_2__ {size_t len; } ;
struct mkuz_blk {TYPE_1__ info; int /*<<< orphan*/  data; int /*<<< orphan*/  alen; } ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 size_t ZSTD_compress2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ZSTD_getErrorName (size_t) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 

void
mkuz_zstd_compress(void *p, const struct mkuz_blk *iblk, struct mkuz_blk *oblk)
{
	ZSTD_CCtx *cctx;
	size_t rc;

	cctx = p;

	rc = ZSTD_compress2(cctx, oblk->data, oblk->alen, iblk->data,
	    iblk->info.len);
	if (ZSTD_isError(rc))
		errx(1, "could not compress data: ZSTD_compress2: %s",
		    ZSTD_getErrorName(rc));

	oblk->info.len = rc;
}