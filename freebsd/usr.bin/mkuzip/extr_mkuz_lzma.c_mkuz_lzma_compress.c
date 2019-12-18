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
struct TYPE_6__ {scalar_t__ avail_out; scalar_t__ avail_in; int /*<<< orphan*/  next_out; int /*<<< orphan*/  next_in; } ;
struct mkuz_lzma {TYPE_2__ strm; int /*<<< orphan*/  filters; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct mkuz_blk {scalar_t__ alen; TYPE_1__ info; int /*<<< orphan*/  data; } ;
typedef  scalar_t__ lzma_ret ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_CHECK_CRC32 ; 
 int /*<<< orphan*/  LZMA_FINISH ; 
 scalar_t__ LZMA_MEMLIMIT_ERROR ; 
 scalar_t__ LZMA_OK ; 
 scalar_t__ LZMA_STREAM_END ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ lzma_code (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_end (TYPE_2__*) ; 
 scalar_t__ lzma_stream_encoder (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mkuz_lzma_compress(void *p, const struct mkuz_blk *iblk, struct mkuz_blk *oblk)
{
	lzma_ret ret;
	struct mkuz_lzma *ulp;

	ulp = (struct mkuz_lzma *)p;

	ret = lzma_stream_encoder(&ulp->strm, ulp->filters, LZMA_CHECK_CRC32);
	if (ret != LZMA_OK) {
		if (ret == LZMA_MEMLIMIT_ERROR)
			errx(1, "can't compress data: LZMA_MEMLIMIT_ERROR");

		errx(1, "can't compress data: LZMA compressor ERROR");
	}

	ulp->strm.next_in = iblk->data;
	ulp->strm.avail_in = iblk->info.len;
	ulp->strm.next_out = oblk->data;
	ulp->strm.avail_out = oblk->alen;

	ret = lzma_code(&ulp->strm, LZMA_FINISH);

	if (ret != LZMA_STREAM_END)
		errx(1, "lzma_code FINISH failed, code=%d, pos(in=%zd, "
		    "out=%zd)", ret, (iblk->info.len - ulp->strm.avail_in),
		    (oblk->alen - ulp->strm.avail_out));

#if 0
	lzma_end(&ulp->strm);
#endif

	oblk->info.len = oblk->alen - ulp->strm.avail_out;
}