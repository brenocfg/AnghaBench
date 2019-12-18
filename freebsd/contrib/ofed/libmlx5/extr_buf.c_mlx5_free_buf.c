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
struct mlx5_buf {int /*<<< orphan*/  buf; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_dofork_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5_free_buf(struct mlx5_buf *buf)
{
	ibv_dofork_range(buf->buf, buf->length);
	free(buf->buf);
}