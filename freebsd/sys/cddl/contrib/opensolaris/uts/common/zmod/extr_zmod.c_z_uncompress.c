#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zs ;
struct TYPE_6__ {size_t avail_in; size_t avail_out; size_t total_out; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; void* next_out; int /*<<< orphan*/ * next_in; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  uchar_t ;

/* Variables and functions */
 int DEF_WBITS ; 
 int Z_BUF_ERROR ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int inflateEnd (TYPE_1__*) ; 
 int inflateInit2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zfs_zcalloc ; 
 int /*<<< orphan*/  zfs_zcfree ; 

int
z_uncompress(void *dst, size_t *dstlen, const void *src, size_t srclen)
{
	z_stream zs;
	int err;

	bzero(&zs, sizeof (zs));
	zs.next_in = (uchar_t *)src;
	zs.avail_in = srclen;
	zs.next_out = dst;
	zs.avail_out = *dstlen;
	zs.zalloc = zfs_zcalloc;
	zs.zfree = zfs_zcfree;

	/*
	 * Call inflateInit2() specifying a window size of DEF_WBITS
	 * with the 6th bit set to indicate that the compression format
	 * type (zlib or gzip) should be automatically detected.
	 */
	if ((err = inflateInit2(&zs, DEF_WBITS | 0x20)) != Z_OK)
		return (err);

	if ((err = inflate(&zs, Z_FINISH)) != Z_STREAM_END) {
		(void) inflateEnd(&zs);
		return (err == Z_OK ? Z_BUF_ERROR : err);
	}

	*dstlen = zs.total_out;
	return (inflateEnd(&zs));
}