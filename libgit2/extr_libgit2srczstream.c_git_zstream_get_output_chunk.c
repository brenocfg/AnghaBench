#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uInt ;
struct TYPE_7__ {size_t avail_in; size_t avail_out; void* next_out; int /*<<< orphan*/ * next_in; } ;
struct TYPE_6__ {scalar_t__ in_len; scalar_t__ type; TYPE_3__ z; scalar_t__ in; int /*<<< orphan*/  flush; int /*<<< orphan*/  zerr; } ;
typedef  TYPE_1__ git_zstream ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 scalar_t__ GIT_ZSTREAM_INFLATE ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int /*<<< orphan*/  deflate (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inflate (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ zstream_seterr (TYPE_1__*) ; 

int git_zstream_get_output_chunk(
	void *out, size_t *out_len, git_zstream *zstream)
{
	size_t in_queued, in_used, out_queued;

	/* set up input data */
	zstream->z.next_in = (Bytef *)zstream->in;

	/* feed as much data to zlib as it can consume, at most UINT_MAX */
	if (zstream->in_len > UINT_MAX) {
		zstream->z.avail_in = UINT_MAX;
		zstream->flush = Z_NO_FLUSH;
	} else {
		zstream->z.avail_in = (uInt)zstream->in_len;
		zstream->flush = Z_FINISH;
	}
	in_queued = (size_t)zstream->z.avail_in;

	/* set up output data */
	zstream->z.next_out = out;
	zstream->z.avail_out = (uInt)*out_len;

	if ((size_t)zstream->z.avail_out != *out_len)
		zstream->z.avail_out = UINT_MAX;
	out_queued = (size_t)zstream->z.avail_out;

	/* compress next chunk */
	if (zstream->type == GIT_ZSTREAM_INFLATE)
		zstream->zerr = inflate(&zstream->z, zstream->flush);
	else
		zstream->zerr = deflate(&zstream->z, zstream->flush);

	if (zstream_seterr(zstream))
		return -1;

	in_used = (in_queued - zstream->z.avail_in);
	zstream->in_len -= in_used;
	zstream->in += in_used;

	*out_len = (out_queued - zstream->z.avail_out);

	return 0;
}