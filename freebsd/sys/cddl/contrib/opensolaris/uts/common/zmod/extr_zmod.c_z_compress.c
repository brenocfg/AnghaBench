#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  Z_DEFAULT_COMPRESSION ; 
 int z_compress_level (void*,size_t*,void const*,size_t,int /*<<< orphan*/ ) ; 

int
z_compress(void *dst, size_t *dstlen, const void *src, size_t srclen)
{
	return (z_compress_level(dst, dstlen, src, srclen,
	    Z_DEFAULT_COMPRESSION));
}