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
 int Z_BUF_ERROR ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int deflateEnd (TYPE_1__*) ; 
 int deflateInit (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zfs_zcalloc ; 
 int /*<<< orphan*/  zfs_zcfree ; 

int
z_compress_level(void *dst, size_t *dstlen, const void *src, size_t srclen,
    int level)
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

	if ((err = deflateInit(&zs, level)) != Z_OK)
		return (err);

	if ((err = deflate(&zs, Z_FINISH)) != Z_STREAM_END) {
		(void) deflateEnd(&zs);
		return (err == Z_OK ? Z_BUF_ERROR : err);
	}

	*dstlen = zs.total_out;
	return (deflateEnd(&zs));
}