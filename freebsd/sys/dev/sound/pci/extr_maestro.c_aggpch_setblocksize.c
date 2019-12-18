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
typedef  int u_int32_t ;
struct agg_chinfo {int speed; int stereo; int qs16; int blklen; int buflen; int /*<<< orphan*/  buffer; TYPE_1__* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_2__ {int bufsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  RANGE (int,int,int) ; 
 int sndbuf_getblkcnt (int /*<<< orphan*/ ) ; 
 int sndbuf_getblksz (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_resize (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sndbuf_setblkcnt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sndbuf_setblksz (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int32_t
aggpch_setblocksize(kobj_t obj, void *data, u_int32_t blocksize)
{
	struct agg_chinfo *ch = data;
	int blkcnt;

	/* try to keep at least 20msec DMA space */
	blkcnt = (ch->speed << (ch->stereo + ch->qs16)) / (50 * blocksize);
	RANGE(blkcnt, 2, ch->parent->bufsz / blocksize);

	if (sndbuf_getsize(ch->buffer) != blkcnt * blocksize) {
		sndbuf_resize(ch->buffer, blkcnt, blocksize);
		blkcnt = sndbuf_getblkcnt(ch->buffer);
		blocksize = sndbuf_getblksz(ch->buffer);
	} else {
		sndbuf_setblkcnt(ch->buffer, blkcnt);
		sndbuf_setblksz(ch->buffer, blocksize);
	}

	ch->blklen = blocksize / 2;
	ch->buflen = blkcnt * blocksize / 2;
	return blocksize;
}