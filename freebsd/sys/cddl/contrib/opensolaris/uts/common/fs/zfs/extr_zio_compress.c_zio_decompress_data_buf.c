#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* ci_decompress ) (void*,void*,size_t,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ci_level; } ;
typedef  TYPE_1__ zio_compress_info_t ;
typedef  scalar_t__ uint_t ;
typedef  enum zio_compress { ____Placeholder_zio_compress } zio_compress ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZIO_COMPRESS_FUNCTIONS ; 
 int stub1 (void*,void*,size_t,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* zio_compress_table ; 

int
zio_decompress_data_buf(enum zio_compress c, void *src, void *dst,
    size_t s_len, size_t d_len)
{
	zio_compress_info_t *ci = &zio_compress_table[c];
	if ((uint_t)c >= ZIO_COMPRESS_FUNCTIONS || ci->ci_decompress == NULL)
		return (SET_ERROR(EINVAL));

	return (ci->ci_decompress(src, dst, s_len, d_len, ci->ci_level));
}