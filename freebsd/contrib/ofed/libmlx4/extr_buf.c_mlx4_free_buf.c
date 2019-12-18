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
struct mlx4_buf {scalar_t__ length; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_dofork_range (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,scalar_t__) ; 

void mlx4_free_buf(struct mlx4_buf *buf)
{
	if (buf->length) {
		ibv_dofork_range(buf->buf, buf->length);
		munmap(buf->buf, buf->length);
	}
}