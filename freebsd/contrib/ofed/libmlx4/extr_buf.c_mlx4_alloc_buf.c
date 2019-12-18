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
struct mlx4_buf {scalar_t__ buf; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int MAP_ANONYMOUS ; 
 scalar_t__ MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  align (size_t,int) ; 
 int errno ; 
 int ibv_dontfork_range (scalar_t__,size_t) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 

int mlx4_alloc_buf(struct mlx4_buf *buf, size_t size, int page_size)
{
	int ret;

	buf->length = align(size, page_size);
	buf->buf = mmap(NULL, buf->length, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (buf->buf == MAP_FAILED)
		return errno;

	ret = ibv_dontfork_range(buf->buf, size);
	if (ret)
		munmap(buf->buf, buf->length);

	return ret;
}