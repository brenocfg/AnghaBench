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
struct mlx4_device {int /*<<< orphan*/  page_size; } ;
struct mlx4_buf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  align (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mlx4_alloc_buf (struct mlx4_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx4_alloc_cq_buf(struct mlx4_device *dev, struct mlx4_buf *buf, int nent,
		      int entry_size)
{
	if (mlx4_alloc_buf(buf, align(nent * entry_size, dev->page_size),
			   dev->page_size))
		return -1;
	memset(buf->buf, 0, nent * entry_size);

	return 0;
}