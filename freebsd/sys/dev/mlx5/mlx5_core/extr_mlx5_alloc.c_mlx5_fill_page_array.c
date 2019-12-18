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
struct mlx5_buf {int npages; int /*<<< orphan*/ * page_list; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

void
mlx5_fill_page_array(struct mlx5_buf *buf, __be64 *pas)
{
	int i;

	for (i = 0; i != buf->npages; i++)
		pas[i] = cpu_to_be64(buf->page_list[i]);
}